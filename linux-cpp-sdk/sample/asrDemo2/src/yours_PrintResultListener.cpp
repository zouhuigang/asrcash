#include <json/json.h>
#include "yours_PrintResultListener.hpp"
#include <iostream>
#include <sstream>
#include <string.h>
#include "asrdemo/Util.hpp"

namespace yours {

PrintResultListener::PrintResultListener(const std::string &prefix) :asrdemo::StatusListener(), _prefix(prefix) {
    // write_log("PrintResultListener constructor");
}

PrintResultListener::~PrintResultListener() {
    // write_log("PrintResultListener DeConstructor");
}

/**
 * 识别开始
 */
void PrintResultListener::on_start_working() {
    // write_log("开始识别");
}

/**
 * 检查到一句话开始
 */
void PrintResultListener::on_start() {
    // write_log("检测到一句话开始");
}

/**
 * 检查到一句话结束
 */
void PrintResultListener::on_end() {
    // write_log("检测到一句话结束");
}

/**
 * 临时识别结果
 *
 * json IN 含有临时结果的json
 */
// void PrintResultListener::on_flush_data(const std::string &json) {
//     write_log("临时结果：" + json);
// }

/**
 * 一句话识别结束。
 * 未开启长语音时，表示整个识别过程结束，BDSpeechSDK实例处于空闲状态
 *
 * json IN 含有最终结果的json
 */
void PrintResultListener::on_finish(const std::string &new_json_result) {
    // //解析json
    Json::Reader reader;
    Json::Value value;//Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array 
    std::string sn; 
    std::string baiduResultTxt;
    if(reader.parse(new_json_result,value))
    {
            if(!value["origin_result"]["sn"].isNull()){
            sn=value["origin_result"]["sn"].asString();
            int file_size = value["results_recognition"].size();
            int first=0;
            if (file_size>0){
                baiduResultTxt=value["results_recognition"][first].asString();
            }
            }
    }

    R_baiduSdkResultTxt = R_baiduSdkResultTxt+ baiduResultTxt;

    // write_log("识别结果：" + R_baiduSdkResultTxt);
}

void PrintResultListener::on_nlu(const std::string &json) {
    write_log("语义理解结果：" + json);
}

/**
 * 长语音识别结束，（长语音 = 多个“一句话”的识别过程）
 * 表示整个识别过程结束，BDSpeechSDK实例处于空闲状态
 */
void PrintResultListener::on_long_speech_end() {
    write_log("长语音结束");
}

/**
 * 识别出错
 * 表示整个识别过程结束，BDSpeechSDK实例处于空闲状态
 *
 * err_domain IN 错误领域
 * err_code IN 具体错误码
 * err_desc IN 错误描述
 * sn IN 一句话的识别过程中的logId
 */
void PrintResultListener::on_error(int err_domain, int err_code, const std::string &err_desc, const std::string &sn) {
    std::ostringstream oss;
    oss << "识别错误， err_domain=" << err_domain << " ;err_code=" << err_code << " ;err_desc=" << err_desc << " ;sn= "
        << sn;
    write_log(oss.str());
}

/**
 * 识别被用户取消
 * 表示整个识别过程结束，BDSpeechSDK实例处于空闲状态
 */
void PrintResultListener::on_cancel() {
    write_log("用户取消");
}

void PrintResultListener::write_log(const std::string str) const {
    std::cout.flush();
    std::ostringstream os;
    os << "[" << asrdemo::Util::get_gmt_time() << "][" << _prefix << "] :" << str << std::endl;
    std::cout << os.str();
}


//string转char
char *PrintResultListener::stringTochar(std::string str){
       char* jsonString=new char[strlen(str.c_str())+1];
       strcpy(jsonString, str.c_str());
       return jsonString;
}

} /* namespace asrdemo */
