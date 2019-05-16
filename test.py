#!/usr/bin/python
# -*- coding:utf-8 -*-
import ctypes
import json
import time

so = ctypes.cdll.LoadLibrary
lib = so('./libasrv2.so')

# result1=lib.max(1,2)
# print(result1)

#解析返回的c++ string
# cp /home/linux-cpp-sdk/sample/asr/src/libasr.so /home/wwwroot/asrcash/libasr.so
# cp /home/linux-cpp-sdk/sample/asrDemo2/run/lib/libasrdemoall.so /home/wwwroot/asrcash/libasrdemoall.so
# mv /home/linux-cpp-sdk/sample/asrDemo2/src/libasrv2.so /home/wwwroot/asrcash/libasrv2.so
lib.speek.restype = ctypes.c_char_p
params=["/home/wwwroot/account-book/api/app/upload/5/audio/35034d9a-f437-47fa-838e-04acd9eb207d.pcm"]
start =time.perf_counter()
sv=lib.speek(bytes(json.dumps(params),"utf8"))
end = time.perf_counter()
print('Running time: %s Seconds'%(end-start))

print(sv.decode('utf-8'))


'''
g++ -shared -o src/libasr.so  ./src/asr.cpp -I../../include -I../../include/ASR  
-Wall -O0 -fPIC -g -D__LINUX__ -Wno-unknown-pragmas -D_GLIBCXX_USE_CXX11_ABI=0  
-std=c++11 ../../lib/libBDSpeechSDK.a ../../extern/lib/libjsoncpp.a 
../../extern/lib/libcurl.a ../../extern/lib/libiconv.a 
../../extern/lib/libz.a ../../extern/lib/libssl.a 
../../extern/lib/libcrypto.a ../../extern/lib/libuuid.a -lrt -ldl -lpthread 


---

g++ -shared -fPIC -g yours_main.cpp   -L../../../lib -L../../../extern/lib \
-lBDSpeechSDK -lcurl -liconv -lz -lssl -lcrypto -luuid  \
-lrt -ldl -lpthread  -o  lib/libasrdemoall.so
'''