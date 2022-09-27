#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char*argv[]){
	int childExitStatus;
	int flag;
	
	while(1){
	printf("Please chhose your number: \n");
	printf("1-> Hello  2-> World  0-> exit    ->");

	char buffer [10];
	fgets(buffer,10,stdin);
	//could check any digit
	flag = atoi ((const char*) buffer);

    	pid_t ws;
	pid_t pID = fork();
	
	if(pID < 0){
	printf("Failed to fork");
	exit(1);
	}
	else if (pID == 0){
		if(flag == 1){
		//check if there is execytive files
		//NULL could be change into argv, future could use option arguments
		execv("./hello",NULL);
		} else if(flag == 2){
		execv("./world",NULL);
		} else if (flag == 0){
		//break?
		exit(0);
		} else {
		printf("Wrong input!");
		}
	}
	else
	{
	//wait(&cgildExitstatus)
	ws = waitpid(pID,&childExitStatus, WUNTRACED);
	//check if it exist
	printf("Child process ended. pid was %d \n",ws);
	}
	}
	return 0;
}
