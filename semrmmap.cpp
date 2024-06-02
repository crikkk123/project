
// 有名信号量用于不相关进程间同步   读线程

#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include <sys/mman.h>
#include<pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

#define N 10

struct student
{
    int a,b;
};

int main(){
    int fd = open("./mmap.txt",O_RDWR);

    sem_t* sem_space = sem_open("sem_space",O_CREAT,0644,N);
    sem_t* sem_full = sem_open("sem_full",O_CREAT,0644,0);

    student* p = (student*)mmap(NULL,sizeof(sizeof(student)*N),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        perror("mmap error");
        exit(1);
    }
    int i = 0;
    while(1){
        sem_wait(sem_full);
        printf("----------- a =  %d,b = %d\n",p[i].a,p[i].b);
        sem_post(sem_space);
        i = (i+1)%N;
        sleep(1);
    }
    return 0;
}