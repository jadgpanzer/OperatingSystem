#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#define MY_CALL_NUMBER 335
int main(){
	int pid, flag, nicevalue;
    	int prev_prio, prev_nice, cur_prio, cur_nice;
    	int result;

    	printf("Please input variable(pid, flag, nicevalue): ");
    	scanf("%d%d%d", &pid, &flag, &nicevalue);

    	result = syscall(MY_CALL_NUMBER, pid, 0, nicevalue, &prev_prio,
                     &prev_nice);
    	if (result == 14)
    	{
        	printf("ERROR!");
        	return 1;
    	}

    	if (flag == 1)
    	{
        	syscall(MY_CALL_NUMBER, pid, 1, nicevalue, &cur_prio, &cur_nice);
        	printf("Original priority is: [%d], original nice is [%d]\n", prev_prio,prev_nice);
        	printf("Current priority is : [%d], current nice is [%d]\n", cur_prio,cur_nice);
    	}
    	else if (flag == 0)
    	{
        	printf("Current priority is : [%d], current nice is [%d]\n", prev_prio,prev_nice);
    	}
    return 0;
}
