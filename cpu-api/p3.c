#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
	printf("Hello world (pid:%d)\n", (int)getpid());
	int rc = fork();
	if (rc<0){
	fprintf(stderr,"fork failed\n");
	exit(1);
	}else if (rc==0){
	 printf("Hello, I am child (pid:%d)\n", (int) getpid());
	 char *myargs[3];//strdup()字符串拷贝函数
	 myargs[0] = strdup ("wc");//program:"wc",word count
	 myargs[1] = strdup ("p3.c");//argument:file to count需要统计的文件
	 myargs[2] = NULL; //marks end of array
	 //exec()函数簇可以使子进程摆脱和父进程内容的相似性
	 //执行一个完全不同的程序。
	 execvp(myargs[0],myargs);//runs word count，统计行，单词，字节数
	 printf("this shouldn't print out");
	 }else {
	   int wc = wait(NULL);
	   printf("Hello, I am parent of %d (wc: %d) (pid:%d)\n",
		rc, wc, (int) getpid());
	   }
	return 0;
}
