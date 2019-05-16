#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "yours_PrintResultListener.hpp"
#include "asrdemo/AsrdemoController.hpp"
#include "asrdemo/Util.hpp"
#include <json/json.h>
#include <string.h>

using namespace std;

//导出c函数
extern "C"{
    int max(int, int);
    char *speek(char *jsonTxt);
}

/**识别单个文件*/
static void recog_one_file(const std::string &filename,std::string &resultTxt);

// 调用set_config函数，写入sdk的配置参数
static void _config(asrdemo::AsrdemoController &controller);

// 按320字节大小，将数据post到sdk中。
static bool _post_data(istream &io, asrdemo::AsrdemoController &controller, int &sleep_ms, string &error_msg);

// 判断流是否结束或异常(io.eof())，结束的话，调用post_data_finish_and_stop，告知sdk音频结束
static int _push_data_eof(istream &io, asrdemo::AsrdemoController &controller, string &error_msg);


char * stringTochar(std::string str){
       char* jsonString=new char[strlen(str.c_str())+1];
       strcpy(jsonString, str.c_str());
       return jsonString;
}


int max(int a,int b)
{
    return a>b?a:b;
}
char *speek(char *jsonTxt) {
      //返回值
    char* data=new char[4096];//长度限制
    // data=stringTochar("{\"error\": 2,\"error_description\": \"解析Json失败\"}");
    //解析传过来的json参数
    string resultTxt;
    Json::Reader reader;
    Json::Value value;
    if(reader.parse(jsonTxt,value)){//解析文件
        int therad_num = value.size();
        if(therad_num>1){//超过最大线程数
            data=stringTochar("{\"error\": 1,\"error_description\": \"最多识别一个文件\"}");
            return data;
        }
        for (int i = 0; i < therad_num; ++i) {
            //string filename = "/home/wwwroot/account-book/api/app/upload/5/audio/35034d9a-f437-47fa-838e-04acd9eb207d.pcm";
            string filename = value[i].asString();
            recog_one_file(filename,resultTxt); // 识别一个文件
            data=stringTochar("{\"error\":0,\"list\":[{\"thread_id\":0,\"txt\":\""+resultTxt+"\"}]}");
        }
    }else{
        data=stringTochar("{\"error\": 2,\"error_description\": \"解析Json失败\"}");
        return data;
    }
    return data;
}


static void set_config(bds::BDSSDKMessage &cfg_params) {
    const std::string app_id = "14349685";
    const std::string app_key = "nuvTxjy3xyQcEI1G6GEuWmrg";
    const std::string app_secret = "SMQUd4tnUrRFE7RttNhWb5W7heYLtBId";

    const std::string product_id = "1536"; // 普通话搜索模型(没有逗号）)：1536，普通话搜索模型+语义理解 15361, 普通话输入法模型（有逗号） 1537

    cfg_params.set_parameter(bds::ASR_PARAM_KEY_APP_ID, app_id);
    cfg_params.set_parameter(bds::ASR_PARAM_KEY_CHUNK_KEY, app_key);
    cfg_params.set_parameter(bds::ASR_PARAM_KEY_SECRET_KEY, app_secret);
    cfg_params.set_parameter(bds::ASR_PARAM_KEY_PRODUCT_ID, product_id);
    cfg_params.set_parameter(bds::COMMON_PARAM_KEY_DEBUG_LOG_LEVEL, bds::EVRDebugLogLevelOff); //关闭debug日志 ，上线时请注释此行
    float vad_pause_frame = 30;  //设置vad语句静音切分门限, 30帧= 300ms。 即原始语音静音 300ms后，SDK认为一句话结束
    cfg_params.set_parameter(bds::ASR_PARAM_KEY_MAX_SPEECH_PAUSE, vad_pause_frame);
}


/**
 * 识别一个文件
 */
static void recog_one_file(const std::string &filename,std::string &resultTxt) {
    ifstream io(filename.c_str());

    if (!io || !io.is_open()) {
        cerr << "read file error:" << filename << endl;
        exit(1);
    }

    yours::PrintResultListener listener(filename);
    asrdemo::AsrdemoController controller("testYourApp", "./", listener);
    _config(controller);

    bool will_continue = true;
    int sleep_ms = 0;
    while (will_continue) {
        string error_msg;
        int status = _push_data_eof(io, controller, error_msg); // 判断是否是文件结尾，是的话，结束这个音频文件的SDK调用
        if (status < 0) { // 出错
            cerr << "stop audio data error:" << error_msg << " : " << status << endl;
            will_continue = false;
        } else if (status == 1) { // 文件读完了
            will_continue = false;
            io.close();
        } else { // 正常
            //http://ai.baidu.com/forum/topic/show/497639
            // if (sleep_ms > 0) { //上次_post_data欠的sleep
            //     usleep(sleep_ms * 1000); // 一个音频的需要sleep的总长约等于音频时间，如果不遵守，服务器将可能会返回异常结果。
            // }
            will_continue = _post_data(io, controller, sleep_ms, error_msg); // 继续从io读取一个包传入
            if (!will_continue) { //  _post_data() 调用发生异常
                cerr << "stop audio data error:" << error_msg << " : " << status << endl;
            }
        }
    }

    while (!listener.is_finished()) {
        sleep(1);
    }

    resultTxt=listener.R_baiduSdkResultTxt;
    // cout << "识别完成" << listener.R_baiduSdkResultTxt << endl;
}

static void _config(asrdemo::AsrdemoController &controller) {
    bds::BDSSDKMessage cfg_params;
    std::string error_msg;
    set_config(cfg_params);
    // cout << "Config is :\n  " << asrdemo::Util::params_to_string(cfg_params);
    if (controller.config(cfg_params, error_msg)) {
        cout << "FOR Feedback : Config is filled :\n" << asrdemo::Util::params_to_string(cfg_params) << endl;
    } else {
        cerr << error_msg << " , END!" << endl;
        exit(2);
    }
}

/**
 * 判断流是否结束或异常(io.eof())，结束的话，调用post_data_finish_and_stop，告知sdk音频结束
 */
static int _push_data_eof(istream &io, asrdemo::AsrdemoController &controller, string &error_msg) {
    if (io.eof()) {
        if (!controller.post_data_finish_and_stop(error_msg)) {
            return -1; // 出错
        }
        return 1; // 文件结束，并且告知了sdk音频结束
    }
    return 0; // 文件未结束
}

/**
 * 按320字节大小从io读取，将数据post到sdk中。
 */
static bool _post_data(istream &io, asrdemo::AsrdemoController &controller, int &sleep_ms, string &error_msg) {
    const int audio_buf_len = 320;
    char audio_buf[audio_buf_len];
    int readed_len = 0;

    io.read(audio_buf, audio_buf_len);
    readed_len = io.gcount();
    if (readed_len < 0) {
        error_msg = " readed_len is <0";
        return false;
    }
    if (readed_len == 0) { // 读到0字节
        sleep_ms = 0;
        return true;
    }
    if (!controller.post_audio_data(audio_buf, readed_len, error_msg)) {
        return false;
    }

    sleep_ms = asrdemo::Util::cal_speech_16k_duration_ms(readed_len); // 根据audio_buf_len 计算音频长度 16k采样率

    return true;
}
