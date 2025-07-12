#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	int pid;
	pid = fork();
	
	if(pid < 0){
		perror("Fork failed!");
		exit(1);
	}else if(pid == 0){
		printf("\nChild Process (PID is %d): Running ls -l ...\n\n", getpid());
		execl("/bin/ls", "ls", "-l", NULL);
		perror("execl failed");
		exit(0);
	}else{
		printf("\nParent Process (PID is %d): Going to sleep mode ...\n\n", getpid());
		sleep(3);
		printf("\nParent process: Child process finished\n");
		exit(0);
	}
}
