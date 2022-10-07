//pipe pingpng between parent and child

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int atgc,char* argv[]){
    int pi1[2];
    int pi2[2];
    
    int number;
    
    int p1 = pipe(pi1);
    int p2 = pipe(pi2);
    
    if (p1 < 0 || p2 < 0)
    {
        printf("pipe failed");
        exit(1);
    }
    
    //int childS;
    pid_t pid = fork();
    
	if(pid < 0) {
		printf("fork failed");
		exit(1);
	} else if (pid == 0) {	
	    
	    //printf("I am child\n");
        //printf("child No 1 process ended. pid was :%d\n", (int)getpid());
	    //close(pi1[0]);
	    //write(pi1[0],&number,sizeof(number));
	    while(1){
	    sleep(1);
	    read(pi2[0],&number,sizeof(number));
	    sleep(1);
	    write(pi1[1],&number,sizeof(number));
	    printf("child Received, %d\n", number);
	    }
	    //close(pi1[1]);
		
	} else {
	    number = 12;	
		//printf("I am parent\n");
		//waitpid(pid,&childS,WUNTRACED);
		//printf("pid:%d wc:%d rc:%d\n", (int)getpid(), wc, rc);
		//close(pipefd[1]);
		while(1){
		number++;
		write(pi2[1],&number,sizeof(number));
		sleep(1);
		read(pi1[0],&number,sizeof(number));
		printf("parent Received, %d\n", number);

		}
		//close(pipefd[0]);
		

	}
	return 0;



}
