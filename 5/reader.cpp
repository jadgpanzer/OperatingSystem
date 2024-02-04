#include <stdio.h>
#include <iostream>
#include <syscall.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main(){
	key_t key = ftok(".",100);
	int memory_id = shmget(key,128,IPC_CREAT|0666);
	char* addr = (char*)shmat(memory_id,NULL,0);
	if(addr == 0 ){
		printf("Memory Mapping Error!");
		return 0 ;
	}
	int i = 0 ;
	while(i < 3){
		sleep(5);
		printf("Receive:%s\n",addr);
		i++;
	}
	
	return 0;
}
