#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
int main(int argc,char* argv[]){
	FILE* test_file = fopen("test.txt","r");
	FILE* target_file = fopen("target.txt","r");
	
	struct timespec start_t,end_t;
	double total_t[4];
	int num = 0 ;
	//condition1
	
	printf("conditon1\n");
	char* buf = (char*)malloc(4096*20);
	
	clock_gettime(CLOCK_MONOTONIC,&start_t);
	fread(buf,1,4096,test_file);
	fwrite(buf,1,4096,target_file);
	clock_gettime(CLOCK_MONOTONIC,&end_t);
	total_t[num++]=(end_t.tv_sec-start_t.tv_sec)+(end_t.tv_nsec-start_t.tv_nsec)/1e9;
	//fflush(test_file);
	//fflush(target_file);
	
	//condition2
	printf("conditon2\n");
	free(buf);
	buf = (char*)malloc(4096);
	
	clock_gettime(CLOCK_MONOTONIC,&start_t);
	fread(buf,1024,4096,test_file);
	fwrite(buf,1024,4096,target_file);
	clock_gettime(CLOCK_MONOTONIC,&end_t);
	total_t[num++]=(end_t.tv_sec-start_t.tv_sec)+(end_t.tv_nsec-start_t.tv_nsec)/1e9;
	//fflush(test_file);
	//fflush(target_file);
	
	
	fclose(test_file);
	fclose(target_file);
	
	int test = open("test.txt",0);
	int target = open("target.txt",1);
	
	//condition3
	printf("conditon3\n");
	free(buf);
	buf = (char*)malloc(4096);
	
	clock_gettime(CLOCK_MONOTONIC,&start_t);
	read(test,buf,1);
	write(target,buf,1);
	clock_gettime(CLOCK_MONOTONIC,&end_t);
	total_t[num++]=(end_t.tv_sec-start_t.tv_sec)+(end_t.tv_nsec-start_t.tv_nsec)/1e9;
	
	//conditon4
	printf("conditon4\n");
	free(buf);
	buf = (char*)malloc(4096);
	
	clock_gettime(CLOCK_MONOTONIC,&start_t);
	read(test,buf,1024);
	write(target,buf,1024);
	clock_gettime(CLOCK_MONOTONIC,&end_t);
	total_t[num++]=(end_t.tv_sec-start_t.tv_sec)+(end_t.tv_nsec-start_t.tv_nsec)/1e9;
	close(test);
	close(target);
	for( ; num>0;num--){
		printf("condition%d:%lf\n",4-num,total_t[4-num]);
	}
	return 0;
}
