

    cd /home/linux-cpp-sdk/sample/asr/src

    
    #测试是否正常
    ldd -r libtest.so



    https://blog.csdn.net/stpeace/article/details/76561814





因为算法效率问题所以要在python中调用C, 
先写一个C函数:

cc.cpp:

	int ts(int a, int b) {
	
	    return a * b;
	
	}

编译 :

	 g++ -c -fPIC cc.cpp
	
	 g++ -shared cc.o -o libcc.so

然后在python中调用ts函数:

ts.py:

	from ctypes import *
	
	import os
	
	libcc = cdll.LoadLibrary(os.getcwd() + '/libcc.so')
	
	print libcc.ts(2,3)

运行:

	python ts.py

	出错:******can not find symbol ts

谷歌了一下,发现是因为c++编译后的文件会把函数名改名（为了实现重载功能）

用extern "C"声明后，就会使用c的方式进行编译，编译后的文件中仍然是定义的函数名

所以只要讲c库中的代码改为:

	extern "C"{
	
	    int ts(int, int);
	
	}

	int ts(int a, int b) {
	
	    return a * b;
	
	}



//g++ -o cpptest.so -shared -fPIC cpptest.cpp

	//-o 指定生成的文件名，-shared 指定微共享库，-fPIC 表明使用地址无关代码


https://blog.csdn.net/zj1123583454/article/details/78742694
https://blog.csdn.net/caobin0825/article/details/79637266