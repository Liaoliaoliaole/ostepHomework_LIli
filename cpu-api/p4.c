#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
	printf("Hello world (pid:%d)\n", (int)getpid());
	int rc = fork();
	if (rc<0){
	fprintf(stderr,"fork failed\n");
	exit(1);
	}else if (rc==0){
	 close(STDOUT_FILENO);//重新定向到输出文件
	 open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

	 //重载“wc”程序
	 char *myargs[3];//strdup()字符串拷贝函数
	 myargs[0] = strdup ("wc");//program:"wc",word count
	 myargs[1] = strdup ("p3.c");//argument:file to count需要统计的文件
	 myargs[2] = NULL; //marks end of array
	 //exec()函数簇可以使子进程摆脱和父进程内容的相似性
	 //执行一个完全不同的程序。
	 execvp(myargs[0],myargs);//runs word count，统计行，单词，字节数
	 }else {
	   int wc = wait(NULL);
	   assert(wc>=0);
	   }
	return 0;
}
