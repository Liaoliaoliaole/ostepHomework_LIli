#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
void sighandler(int sig){
printf("In signal handler for signal %d\n",sig);
wait(NULL);
}

int main()
{
	sigset(SIGCHILD,&sighandler);//function pointer ?

	pid_t pid;
	pid = fork();
	if(pid==0){
	printf("child\n");
	printf("child exist\n");
	}else if(pid != -1) {
		printf("Hello parent,pid:%d.\n",getpid());
		printf("parent has forked process %d.\n", pid);
		sleep(60);
		printf("parent exist\n");
	} else {
		printf("error");
	}
	return 0;
}

//if wait after sleep, child gone before parent, there is nothing to wait for, it wait forever. this will end up a zombi process.
//signal handler solve it, when chold exist, signal handler takes a signal give to parent, the parent will not wait for.
