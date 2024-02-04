#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <syscall.h>
#include <unistd.h>
#define SEND_TIMES 5
struct msg_t{ 
         long msg_type;
         /*定义自己的数据内容*/ 
         char message[64];
}; 
int main(int argc,char* argv[]){
	int pid = fork();
	if(pid <0){
		printf("Fork Error");
		return 0;
	}
	if(pid == 0){
	//son process	
		struct msg_t send_buffer = {2,"Hello,this son process"};
		struct msg_t read_buffer = {};
		key_t key = ftok("msg",1);
		int msg_id = msgget(key,IPC_CREAT|0777);
		int i = 0 ;
		while(i < SEND_TIMES){
			sleep(1);
			msgrcv(msg_id,&read_buffer,sizeof(read_buffer.message),i+1,0);	//接收
			printf("son Receive: %s%d\n",read_buffer.message,i+1);
			send_buffer.msg_type = i+1 ;
			msgsnd(msg_id,&send_buffer,sizeof(send_buffer.message),0);		//发送
			printf("Son Send!\n");
			i++ ;
		}
		return 0;
	}
	if(pid > 0){
	//father process
		struct msg_t send_buffer = {0,"Hello,this father process"};
		struct msg_t read_buffer = {};
		key_t key = ftok("msg",1);
		int msg_id = msgget(key,IPC_CREAT|0777);
		int i = 0 ;
		while(i < SEND_TIMES){
			
			send_buffer.msg_type = i+1 ;
			msgsnd(msg_id,&send_buffer,sizeof(send_buffer.message),0);		//发送
			printf("Father Send!\n");
			sleep(1);
			msgrcv(msg_id,&read_buffer,sizeof(read_buffer.message),i+1,0);	//接收
			printf("Father Receive: %s%d\n",read_buffer.message,i+1);
			i++ ;
		}
		return 0;
	}
}
