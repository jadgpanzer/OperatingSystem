#include <stdio.h>
#include <iostream>
#include <syscall.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main(){
	key_t key = ftok(".",100);
	int memory_id = shmget(key,128,IPC_CREAT|0666);		//�������ڴ���
	char* addr = (char*)shmat(memory_id,NULL,0);		//ӳ�乲���ڴ���
	int i = 0 ;
	char str[128];
	while(i<3){
		printf("Input the text you want to write:\n");
		scanf("%s",str);
		strcpy(addr,str);
		i++;
	}
	shmdt(addr);
	shmctl(memory_id, IPC_RMID, addr);					//�رչ����ڴ�
	return 0;
}
