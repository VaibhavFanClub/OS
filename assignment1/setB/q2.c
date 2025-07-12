#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	pid_t pid;
	int rnice;
	pid = fork();
	if(pid < 0){
		perror("Fork failed!");
		exit(1);
	}else if(pid == 0){
		rnice = nice(-3);
		printf("\nChild Process (PID is %d): Assigning higter priority %d\n\n", getpid(), rnice);
		sleep(2);
		exit(0);
	} else{
		printf("\nParent Process (PID is %d)\n", getpid());
		exit(0);
	}
}
