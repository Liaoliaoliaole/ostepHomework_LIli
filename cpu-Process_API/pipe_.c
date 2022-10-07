#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int atgc,char* argv[]){
    int pipefd[2];
    int number=12;
    
    int p=pipe(pipefd);
    
    if(p == -1){
    printf("Pipe error");
    exit(-1);
    }
    
    int childS;
    pid_t pid = fork();
	if(pid < 0) {
		printf("fork failed");
		exit(1);
	} else if (pid == 0) {	
	printf("I am child\n");
        printf("child No 1 process ended. pid was :%d\n", (int)getpid());
	    close(pipefd[0]);
	    write(pipefd[1],&number,sizeof(number));
	    close(pipefd[1]);
		sleep(1);
	} else {	
		printf("I am parent\n");
		waitpid(pid,&childS,WUNTRACED);
		//printf("pid:%d wc:%d rc:%d\n", (int)getpid(), wc, rc);
		close(pipefd[1]);
		read(pipefd[0],&number,sizeof(number));
		close(pipefd[0]);
		printf("Received, %d\n", number);

	}
	return 0;



}
