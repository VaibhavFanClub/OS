#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int pid;
	pid = fork();
	char *args[] = {"ls", "-l", NULL};
	if(pid < 0){
		perror("Fork failed\n");
		exit(1);
	}else if(pid == 0){
		printf("\nChild process (PID is %d): Running ls -l ...\n\n", getpid());
		execvp(args[0], args);
		perror("execvp failed!\n");
		exit(0);
	}else{
		printf("\nParent process (PID is %d): Waiting for child process to complete ...\n\n", getpid());
		wait(NULL);
		perror("Parent Process: Child process finished!\n");
		exit(0);
	}
}
