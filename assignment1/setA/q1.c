#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("Error creating child process!\n");
		exit(1);
	}else if(pid == 0){
		printf("Hello world\nChild PID is %d\n", getpid());
		exit(0);
	}else{
		//wait(NULL);
		printf("Hi\nParent PID is %d\n", getpid());
		exit(0);
	}
}
