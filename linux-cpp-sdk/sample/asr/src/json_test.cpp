#include <json/json.h>
#include <string>
#include <iostream>
using namespace std;

/*
[root@yang json_test0922]# cat makefile
json_test:json_test.cpp
  g++ -o json_test json_test.cpp /usr/lib/libjson_linux-gcc-4.4.7_libmt.a


#测试时的路径
     g++ -o json_test json_test.cpp /root/jsoncpp-src-0.5.0/libs/linux-gcc-4.8.5/libjson_linux-gcc-4.8.5_libmt.a

     可将 libjson_linux-gcc-4.4.7_libmt.a 和 libjson_linux-gcc-4.4.7_libmt.so 拷贝到/usr/lib下， 
本文选择了静态库库文件，将解压后的文件夹下的INCLUDE中的头文件拷贝到/usr/include/json下。

----


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


    g++ -o json_test json_test.cpp /usr/lib/libjson_linux-gcc-4.8.5_libmt.a

    https://blog.csdn.net/laoyang360/article/details/52613262

### 实践

    [root@c3 src]# g++ -o json_test json_test.cpp /usr/lib/libjson_linux-gcc-4.8.5_libmt.a
    [root@c3 src]# ./json_test 
    xx显华化工科技有限公司
    XX经济技术开发区市场监督管理局
    g++ -o json_test json_test.cpp  /home/linux-cpp-sdk/extern/lib/libjson_linux-gcc-4.8.5_libmt.a

*/

int main()
{
string test = "{\"encrptpripid\": \"f2cbfd07bb6b784f0fb5a52e17e1b3930324e1ef9065338f4aa1\", \
\"entname\": \"xx显华化工科技有限公司\",\
  \"enttype\": \"1151\",\
  \"enttypename\": \"法定代表人:\",\
  \"estdate\": \"2003年06月19日\",\
  \"lerep\": \"丰佩川\",\
  \"pripid\": \"106350010220030687030\",\
  \"regno\": \"911706007526952553\",\
  \"regorgname\": \"XX经济技术开发区市场监督管理局\",\
  \"uniscid\":\"91106007526952553\"}";

Json::Reader reader;
Json::Value value;
if(reader.parse(test,value))
{
  if(!value["encrptpripid"].isNull())
  {
  cout << value["entname"].asString() << endl;
  cout << value["regorgname"].asString()<< endl;
  }
}
return 0;
}