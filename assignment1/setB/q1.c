#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	pid_t pid = fork();
	if(pid < 0){
		perror("Fork failed");
		exit(1);
	}else if(pid == 0){
		sleep(5);
		printf("\nChild Process:\n");
		printf("PID: %d\n", getpid());
		printf("PPID (parent): %d\n", getpid());
	}else{
		printf("Parent Process (PID: %d) exiting... \n", getpid());
		exit(0);
	}
	return 0;
}
