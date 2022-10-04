#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
//#include <signal.h>
#include <unistd.h>//pipe().pipe2()
#include <stdlib.h>//fprint

/*void signalHandler(int signal)
{
	printf("Cought signal %d!\n",signal);
	if (signal==SIGCHLD) {
		printf("Child ended\n");
		wait(NULL);
	}
}*/
 
int main()
{
int s;
/*/ We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child*/
    int pi1[2];
    int pi2[2];
    char buf1[30], buf2[30];
//int pipe(int pipefd[2]);
//pipe() creates a pipe, a unidirectional data channel that can be
//used for interprocess communication.  The array pipefd is used to
//return two file descriptors referring to the ends of the pipe.
       
//pipefd[0] refers to the read end of the pipe.  pipefd[1] refers
//to the write end of the pipe.  Data written to the write end of
//the pipe is buffered by the kernel until it is read from the read
//end of the pipe.  
/*pipe () 创建一个管道，一个单向的数据通道，可以
       用于进程间通信。数组pipefd用于
       返回两个引用管道末端的文件描述符。
       pipefd[0]指的是管道的读取端。  pipefd[1]指
       到管道的写端。数据写入写入端
       管道由内核缓冲，直到从读取中读取
       管道的末端。成功时，返回零。出错时，返回 -1，errno为
       设置以指示错误，并且pipefd保持不变。*/
    int p1 = pipe(pi1);
    int p2 = pipe(pi2);
    long temptime;
    struct timeval start, end;
    int i;
    if (p1 < 0 || p2 < 0)
    {
        fprintf(stderr, "pipe failed");
        exit(1);
    }
    int rc = fork();
    for (i = 0; i < 10; ++i)
    {
        if (rc < 0)
        {
            fprintf(stderr, "fork failed");
            exit(1);
        }
        else if (rc == 0)
        {
	   //child process
	   //close(pi1[1]);
            read(pi1[0], buf1, 25);//// Read a string using first pipe
            gettimeofday(&end, NULL);
            printf("%ld\n", end.tv_usec - atol(buf1));
            gettimeofday(&start, NULL);
            sprintf(buf2, "%ld", start.tv_usec);
            //write () 将缓冲区中从buf开始的最多count个字节写入
 	    //文件描述符fd所引用的文件。
	   //ssize_t write(int fd , const void * buf , size_t count );
	    write(pi2[1], buf2, 25);
        }
/*父进程内部：我们首先关闭第一个管道的读取端（pi1[0]
然后通过管道的写入端（pi1[1]）写入字符串。现在父进程将等到子进程完成。
子进程结束后，父进程会关闭第二个管道（pi2[1]）的写端，并通过管道的读端（fd2[0]）读取字符串。
内部子进程：子进程通过关闭管道的写入端（fd1 [1]）读取父进程发送的第一个字符串，
并在读取连接两个字符串并通过fd2管道将字符串传递给父进程后退出。 */
	//// Parent process
        else
        {
            gettimeofday(&start, NULL);
            sprintf(buf1, "%ld", start.tv_usec);
            write(pi1[1], buf1, 25);
            //wait(rc);子进程要一直写，不会退出，进程会阻塞 
/* wait(NULL);
wait(NULL)将阻塞父进程，直到其任何子进程完成。如果子进程在父进程到达之前终止，wait(NULL)则子进程将变为僵尸进程，直到其父进程等待它并从内存中释放。
如果父进程不等待其子进程，而父进程先完成，则子进程将成为孤儿并被分配init为其子进程。而init会等待并释放进程表中的进程条目。
换句话说：父进程将被阻塞，直到子进程向操作系统返回退出状态，然后操作系统返回给父进程。如果子进程在父进程到达 wait(NULL) 之前完成，那么它将读取退出状态，释放进程表中的进程条目并继续执行直到它也完成。*/
	    read(pi2[0], buf2, 25);//read from child
            gettimeofday(&end, NULL);
            printf("%ld\n", end.tv_usec - atol(buf2));
        }
    }
    return 0;
}

