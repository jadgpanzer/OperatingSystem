#include <stdio.h>
#include <iostream>
#include <syscall.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main(){
	key_t key = ftok(".",100);
	int memory_id = shmget(key,128,IPC_CREAT|0666);		//请求共享内存区
	char* addr = (char*)shmat(memory_id,NULL,0);		//映射共享内存区
	int i = 0 ;
	char str[128];
	while(i<3){
		printf("Input the text you want to write:\n");
		scanf("%s",str);
		strcpy(addr,str);
		i++;
	}
	shmdt(addr);
	shmctl(memory_id, IPC_RMID, addr);					//关闭共享内存
	return 0;
}
