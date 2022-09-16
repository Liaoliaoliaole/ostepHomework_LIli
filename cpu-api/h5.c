#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		int wc = wait(NULL);
		printf("child");
        	printf("pid:%d wc:%d rc:%d\n", (int)getpid(), wc, rc);
	} else {
		int wc = wait(NULL);
		printf("parent");
		printf("pid:%d wc:%d rc:%d\n", (int)getpid(), wc, rc);

	}
	return 0;
}
//可以看到子进程wc=-1，他不需要等待谁，父进程需要等待子进程完成。
