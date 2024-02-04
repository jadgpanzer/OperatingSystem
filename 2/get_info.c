#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <syscall.h>
#define CPU_INFO "/proc/loadavg"
#define MEMORY_INFO "/proc/meminfo"
#define SYS_INFO "/proc/stat"
#define UPTIME_INFO "/proc/uptime"

void display_sys_name(){
	printf("\n-------------------------------\n");
	printf("System Name:\nLinux\n");
	printf("\n-------------------------------\n");
}
void display_uptime(){
	printf("System Up Time:\n");
	printf("Uptime Idletime\n");
	char* str = (char*)malloc(128);
	FILE* fp = fopen(UPTIME_INFO,"r");
	fgets(str, 128 , fp);
	printf("%s",str);
	free(str);
	fclose(fp);
	printf("\n-------------------------------\n");
}
void display_cpu(){
	printf("Load Average:\n");
	printf("1min 3min 15min task-number lastest-task\n");
	char* str = (char*)malloc(128);
	FILE* fp = fopen(CPU_INFO,"r");
	fgets(str, 128 , fp);
	printf("%s",str);
	free(str);
	fclose(fp);
	printf("\n-------------------------------\n");
}
void display_mem(){
	printf("Memory Info:\n");
	int i = 0 ;
	FILE* fp = fopen(MEMORY_INFO,"r");
	for( i = 0 ; i < 7 ; i++){
		char* str = (char*)malloc(128);
		
		fgets(str, 128 , fp);
		printf("%s\n",str);
		free(str);
	}
	printf("\n-------------------------------\n");
	fclose(fp);
}
void display_process(){
	printf("Process Info:\n");
	FILE* fp ;
	fp = popen("ps -a","r");
	int i = 0;
	char* str = (char*)malloc(128);
	while( fgets(str, 128 , fp)!=NULL){
		printf("%s",str);
	}
	fclose(fp);
	printf("\n-------------------------------\n");
}
int main(int argc,int* argv[]){
	int i = 0 ;
	for(;i < 1000; i ++){
		display_sys_name();
		display_uptime();
		display_cpu();
		display_mem();
		display_process();
		sleep(2);			//两秒更新一次
		system("clear");
	}
}
