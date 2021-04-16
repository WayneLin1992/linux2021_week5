#include <stdio.h>
#include <stdlib.h>
#define THREAD_INTERVAL 500

#define cr_start()       \
    int __s = 0;           \
    switch(__s){        \
        case 0:
#define cr_yield{     \
    __s =  __LINE__;\
    usleep(THREAD_INTERVAL); \
    return;                 \
    case __LINE__:;  \
}
#define cr_end()    \
    }                       \
    __s = 0;

void thread1(){
    cr_start();
    for(;;){
        printf("thread1\n");
        cr_yield;
    }
    cr_end();
}

void thread2(){
    cr_start();
    for(;;){
        printf("thread2\n");
        cr_yield;
    }
    cr_end();
}

int main()
{
    thread1();
    thread2();
    return 0;
}
