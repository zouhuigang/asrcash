/**
 * file: test.cpp
 *  g++ test.cpp -lpthread && ./a.out
 * Copyright © 2015-2065 www.twle.cn. All rights reserved.
 */

#include <stdio.h>
#include <pthread.h>
#include <typeinfo>
// 定义一个结构体作为参数
struct thread_data{
   int  tid;
   const char *msg;
};


// 线程要运行的函数

void* greeting(void* args)
{
    struct thread_data *data;

    data = (struct thread_data *) args;

    char* newStr=new char[100];
    // sprintf(newStr,"%s%d%c","test",1,'2');
    sprintf(newStr,"new_%s_bbb",data->msg);
    data->msg=newStr;
    return NULL;
}

// 定义线程数量
#define NUM_THREADS 5


// 定义 5 个问候对象
const char *sayto[5] = {
    "Python",
    "PHP",
    "Perl",
    "www.twle.cn",
    "C++"
};


int main()
{
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];

    struct thread_data td[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; ++i)
    {
        td[i].tid = i+1;
        td[i].msg = sayto[i];

        int ret = pthread_create(&tids[i], NULL, greeting, (void *)&(td[i]));
        if (ret != 0)
        {
            printf("pthread_create error: error_code=%d\n",ret);
        }
    }


    for (int i = 0; i < NUM_THREADS; ++i) {
            int ret = pthread_join(tids[i], NULL); // 等待所有线程结束
            if (ret != 0) {
                printf("pthread_join error: error_code=%d\n",ret);
            }
            printf("result:%s\n",td[i].msg);
            

    }

    pthread_exit(NULL);

    return 0;
}