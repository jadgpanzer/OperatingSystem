#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int function(){
	//该函数的功能是执行ps 命令并将当前时间和命令的输出写至文件 ps.log 尾部
	char* info = (char*)malloc(1024);
	int i = 0 ;
	char file_name[] = "ps.log";
	FILE* log = fopen(file_name,"w");
	for(i=0 ;i<4 ;i++){
		
		FILE* fp ;
		fp = popen("ps","r");
		fread(info,1,1024,fp);
		fwrite(info,1,1024,log);
		time_t this_time;
		time(&this_time);
		struct tm *local_time = localtime(&this_time);
		fprintf(log,"\nTime:%d-%d-%d\n",local_time->tm_hour,local_time->tm_min,local_time->tm_sec);
		sleep(10);					//10秒的间隔
		fflush(log);
		fflush(fp);
		printf("ps command\n");
	}
	return 0;
}
int main(int argc,char* argv[]){
	int pid = -1;
	pid = fork();
	if(pid == 0){
		printf("Parents Process Exits!\n");
		exit(0);									//父进程退出
	}
	else if(pid > 0){
		printf("This is a daemod process!\n");
		pid = setsid();								//创建一个新的会话
		function();									//调用function函数
	}
	printf("deamod process exit!\n");
	return 0;
}
