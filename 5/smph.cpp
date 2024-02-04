#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <semaphore.h>
#include <pthread.h>
#define BUFFER_SIZE 32
int used_buffer_size;		//缓存大小
char buffer[BUFFER_SIZE];	//缓存区

sem_t read_sem;

void *product(void* ptr){
	int p = 0;
	while(p < 6){
		sleep(1);
		while(used_buffer_size >= BUFFER_SIZE);		//无空闲区可用，等待
		sem_wait(&read_sem);						//P
		for(int i = 0 ; i < BUFFER_SIZE ; i++){
			buffer[i] = 'a'+ p;
		}
		
		used_buffer_size = BUFFER_SIZE ;
		printf("Producter: Buffer Write\n");
		sem_post(&read_sem);						//V
		p ++ ;
	}
	return 0;
}
void *consume(void* ptr){
	int p = 0; 
	while(p < 6){
		while(used_buffer_size <= 0);	//无数据可用，等待
		sleep(1);
		sem_wait(&read_sem);
		printf("Consumer: Get Buffer=\n%s\n",buffer);
		int i = 0;
		while(i < BUFFER_SIZE){
			buffer[i]  = 0;
			i ++;
		}
		used_buffer_size = 0 ;
		sem_post(&read_sem);
		p++;
	}
	return 0;
}
int main(){
	sem_init(&read_sem,0,1);			//信号量初始化
	used_buffer_size = 0 ;
	pthread_t producter ;
	int tid_0 = pthread_create(&producter,NULL,product,NULL);
	if(tid_0 < 0){
		printf("Pthread creat error!\n");
		return 0;
	}
	pthread_t consumer ;
	int tid_1 = pthread_create(&consumer,NULL,consume,NULL);
	if(tid_1 < 0){
		printf("Pthread creat error!\n");
		return 0;
	}
	printf("Pthread creat success\n");
	pthread_join(producter,NULL);
	pthread_join(consumer,NULL);
	sem_destroy(&read_sem);			//销毁信号量
	return 0;
}
