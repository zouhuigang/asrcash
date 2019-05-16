CC=g++
TARGET=libasrv2.so
SRC=.
#g++ -shared -fPIC -g yours_main.cpp   -L../../../lib -L../../../extern/lib -lBDSpeechSDK -lcurl -liconv -lz -lssl -lcrypto -luuid  -lrt -ldl -lpthread  -o libasrdemoall.so

#注入的静态库
LIB_A=-L../../../lib -L../../../extern/lib ../../../lib/libBDSpeechSDK.a -lcurl -liconv -lz -lssl -lcrypto -luuid ../../../extern/lib/libjsoncpp.a 

#包含include文件
INCLUDE=-I../../../include -I../../../include/ASR -I/home/linux-cpp-sdk/sample/asrDemo2/run/include/asrdemo

#设置
SETTING=-Wall -O0 -fPIC -g -D__LINUX__ -Wno-unknown-pragmas -D_GLIBCXX_USE_CXX11_ABI=0  -std=c++11

$(TARGET):$(SRC)
	$(CC) -shared  *.cpp  asrdemo/*.cpp  $(SETTING) $(INCLUDE) $(LIB_A) -lrt -ldl -lpthread  -o  $(TARGET)