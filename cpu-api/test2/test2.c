#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char*argv[]){
	while(1){
	
	printf("Please chhose your number: \n");
	printf("1-> Hello  2-> World  0-> exit    ->");

	int childExitStatus;
	int flag;
	char buffer [10];
	fgets(buffer,10,stdin);
	flag = atoi ((const char*) buffer);

    pid_t ws;
	pid_t pID = fork();
	if(pID < 0){
	printf("Failed to fork");
	exit(1);
	}
	else if (pID == 0){
		if(flag == 1){
		execv("./hello",NULL);
		} else if(flag == 2){
		execv("./world",NULL);
		} else if (flag == 0){
		exit(0);
		} else {
		printf("Wrong input!");
		}
	}
	else
	{
	ws = waitpid(pID,&childExitStatus, WUNTRACED);
	printf("Child process ended. pid was %d \n",ws);
	}
	}
	return 0;
}
