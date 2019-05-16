https://www.cnblogs.com/pluviophile/p/cpp11-future.html

https://blog.csdn.net/CJ_star/article/details/54379435

https://blog.csdn.net/guilanl/article/details/50150463


http://zhangxiaoya.github.io/2015/05/15/multi-thread-of-c-program-language-on-linux/

https://www.twle.cn/l/yufei/cplusplus/cplusplus-basic-multithreading.html

http://www.cnitblog.com/guopingleee/archive/2008/10/10/50047.html

多线程获取函数的返回值


### 安装jsoncpp库

    yum install scons

    下载:
    https://sourceforge.net/projects/jsoncpp/

    tar -zvxf jsoncpp-src-0.5.0.tar.gz

    cd /root/jsoncpp-src-0.5.0
    scons platform=linux-gcc

### 拷贝

    mv /root/jsoncpp-src-0.5.0/libs/linux-gcc-4.8.5/libjson_linux-gcc-4.8.5_libmt.so /usr/lib
    mv /root/jsoncpp-src-0.5.0/libs/linux-gcc-4.8.5/libjson_linux-gcc-4.8.5_libmt.a /usr/lib

    cp -r /root/jsoncpp-src-0.5.0/include/json/ /usr/include/json/


### 运行测试文件

    g++ -o json_test json_test.cpp /usr/lib/libjson_linux-gcc-4.8.5_libmt.a


### 引入进项目

项目根目录:/home/linux-cpp-sdk

将/usr/lib/libjson_linux-gcc-4.8.5_libmt.a文件拷贝到/home/linux-cpp-sdk/extern/lib目录下面

	cp /usr/lib/libjson_linux-gcc-4.8.5_libmt.a  /home/linux-cpp-sdk/extern/lib

引用文件include:
	
	cp -r  /usr/include/json/ /home/linux-cpp-sdk/extern/include

修改makefile：

	$(EXTERN_PATH)/libjson_linux-gcc-4.8.5_libmt.a


### 遇到问题

    jsoncpp发现在Linux用g++进行编译的boost静态库被动态库引用的时候会报错

    `.rodata' can not be used when making a shared object; recompile with -fPIC

    上网一搜，发现boost编译出静态库的时候没有加-fPIC（通常动态库需要加这个东西，进行地址无关的处理，静态库不需要）。 
    后来在测试了一下，如果用上述的静态库链接到应用程序中是没有问题的，但是连接到动态库中存在问题。也难怪，除非你编一个不带-fPIC的动态库。一个地址无关的.so文件怎么可能链接一个带有地址信息的.a文件呢，想想都有问题。 
    https://blog.csdn.net/lonelysky/article/details/77650613
    https://github.com/open-source-parsers/jsoncpp/issues/708

    g++ json_reader.cpp json_value.cpp json_writer.cpp -fPIC -Wall -shared -o ../../build/x64/release/libjson.so -I../../include -I.




###### 重新编译jsoncpp为静态文件

    cd ~ &&  mkdir arm_jsoncpp
    cp  -r  /root/jsoncpp-src-0.5.0/include   /root/arm_jsoncpp/ 
    cp  /root/jsoncpp-src-0.5.0/src/lib_json/*  /root/arm_jsoncpp/
    cd /root/arm_jsoncpp/
    #静态库
    gcc  -c  *.cpp  -I./include -fPIC
    ar cr libjsoncpp.a *.o
    #动态库
    gcc -shared -fPIC *.cpp -I./include -o libjsoncpp.so

    #参考文档
    https://www.cnblogs.com/leviatan/p/8394740.html
    https://www.cnblogs.com/guxuanqing/p/7513251.html



https://blog.csdn.net/u013430507/article/details/83148314


https://stackoverflow.com/questions/12500069/ctypes-how-to-pass-string-from-python-to-c-function-and-how-to-return-string

https://www.cnblogs.com/JUSTSOSOBLOG/p/7502302.html

https://xidui.github.io/2015/08/23/python-%E8%B0%83%E7%94%A8C-ctypes%E5%BA%93%E5%B0%9D%E8%AF%95/