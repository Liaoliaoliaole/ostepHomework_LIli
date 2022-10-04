#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){	
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printf("Child: hello!\n");
	} else {
	sleep(10); 
	 printf("Parent: goodbye!\n");
	}

	return 0;
}
