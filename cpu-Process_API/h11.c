#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char*argv[]){
    int child_status, grandchild_status;

    pid_t child;
    child = fork();

    if(child <0){
        printf("Fork failed!\n");
        exit(1);
    }else if(child == 0){
        //first child process
        printf("Child, pid: %d \n", getpid());

        pid_t grandchild;
        grandchild = fork();

        if(grandchild<0){
            printf("Fork failed!\n");
            exit(1);
        }else if(grandchild==0){
        //grandchild process
        printf("Grandchild, pid: %d \n", getpid());
        sleep(3);
        }else{
            //child as parent process
            waitpid(grandchild, &grandchild_status,0);
            if (WIFEXITED(grandchild_status))
                printf("grandchild has exited with exit code %d\n", WEXITSTATUS(grandchild_status));
            else
                printf("grandchild has terminated abnormally\n");
        }
    }else{
        //parent process
        printf("Parent pid: %d \n", getpid());
        waitpid(child,&child_status,0);
        if (WIFEXITED(child_status))
            printf("child has exited with exit code %d\n", WEXITSTATUS(child_status));
        else
            printf("child has terminated abnormally\n"); 

        printf("parent has exited with exit code %d\n", WEXITSTATUS(child_status)); 
    }

    return 0;
}