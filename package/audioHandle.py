#pip install baidu-aip
#pip install ffmpy
from aip import AipSpeech
from . import fileHandle
import ffmpy
#API使用参考地址：https://ai.baidu.com/docs#/ASR-Online-Python-SDK/top

APP_ID = '14349685'
API_KEY = 'nuvTxjy3xyQcEI1G6GEuWmrg'
SECRET_KEY = 'SMQUd4tnUrRFE7RttNhWb5W7heYLtBId'

client = AipSpeech(APP_ID,API_KEY,SECRET_KEY)

#转换语音 -f s16le -ac 1 -ar 16000 20190410_133656.pcm
def transformat_voice(inputs,outputs):
    ff = ffmpy.FFmpeg(
        inputs={inputs:None},
        outputs={outputs:'-f s16le -ac 1 -ar 16000'}
        )
    ff.run()


#识别语音
def audios(rootfile):
    audio = fileHandle.getFileContent(rootfile)
    #调取接口,带参数
    audios = client.asr(audio,'pcm',16000,{'dev_pid':1536,})
    #从字典中取出文字
    wd = audios.get('result')
    # print("正在转换[%s]-转换结果[%s]" % (rootfile,wd))
    if wd is None:
        return ''
    elif len(wd)>0:
        return wd[0]
    return wd