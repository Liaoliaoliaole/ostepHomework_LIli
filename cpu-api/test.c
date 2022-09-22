/* Example to demonstrate fork() */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Required by for routine */
#include <sys/types.h>
#include <sys/wait.h>

int globalVariable = 2;

int main(int argc, char *argv[]){
    char sIdentifier[20];
    int  iStackVariable = 20;
    int  childExitStatus;
    pid_t ws;

    pid_t pID = fork();

    if (pID == 0)                /* child */
    {
        /* Code only executed by child process */
        strcpy(sIdentifier,"Child Process: ");
        globalVariable++;
        iStackVariable++;
        sleep(5);
    }
    else if (pID < 0)            /* failed to fork */
    {
        printf("Failed to fork \n");
        exit(1);
        /* Throw exception */
    }
    else                         /* parent */
    {
        /* Code only executed by parent process */

	    strcpy(sIdentifier,"Parent Process: ");
	
        /* use waitpid to hold untill child has exited */
        //pid>0, meaning wait for the child whose  process ID is equal to the value of pid.
        //WUNTRACED also return if a child has  stopped  (but  not  traced  via
         //  ptrace(2)).   Status for traced children which have stopped
          //   is provided even if this option is not specified.

        ws = waitpid(pID,&childExitStatus,WUNTRACED);
        
        printf("Child process ended. pid was: %d\n",ws);
    }

    /* Code executed by both parent and child. */
  
    printf("%s \n",sIdentifier);
    printf(" Global variable: %d \n",globalVariable);
    printf(" Stack variable: %d \n",iStackVariable);
}
