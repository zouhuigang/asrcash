#!/usr/bin/python
#_*_ coding:utf-8 _*_

#pip install baidu-aip
from aip import AipSpeech
import os
import time

#API使用参考地址：https://ai.baidu.com/docs#/ASR-Online-Python-SDK/top

APP_ID = '14349685'
API_KEY = 'nuvTxjy3xyQcEI1G6GEuWmrg'
SECRET_KEY = 'SMQUd4tnUrRFE7RttNhWb5W7heYLtBId'

client = AipSpeech(APP_ID,API_KEY,SECRET_KEY)


#读取文件
def get_file_content(filePath):
    with open(filePath,'rb') as fp:
        return fp.read()
audio = get_file_content("/home/wwwroot/account-book/api/app/upload/5/audio/35034d9a-f437-47fa-838e-04acd9eb207d.pcm")

#调取接口,带参数
start =time.perf_counter()
audios = client.asr(audio,'pcm',16000,{'dev_pid':1536,})
end = time.perf_counter()
print('Running time: %s Seconds'%(end-start))

#从字典中取出文字
wd = audios.get('result')
print(wd,wd[0],str(wd),type(wd))