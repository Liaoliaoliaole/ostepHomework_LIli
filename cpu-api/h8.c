 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/wait.h>

 int main(int argc, char *argv[])
 {
     int fds[2];
     if(pipe(fds)==-1)
     {
         fprintf(stderr, "open pipe failed\n");
         exit(1);
     }
     int rc = fork();
        
     if (rc < 0)
     { // fork failed; exit
         fprintf(stderr, "fork failed\n");
         exit(1);
     }
     else if (rc == 0)
     { // child: redirect standard output to a file
         printf("child1,pid:%d\n",getpid());
         int len;
         char buf[10];
         // 从pipe中读取
         if((len=read(fds[0],buf,6))==-1)
         {
             perror("read from pipe");
             exit(1);
         }
         printf("buf:%s\n",buf);
         exit(0);
     }
     else
     { // parent goes down this path (main)
         //创建第二个子进程
         int rc2 = fork();
         if (rc2 < 0)
         { // fork failed; exit
             fprintf(stderr, "fork failed\n");
             exit(1);
         }
         else if (rc2 == 0)
         { // child: redirect standard output to a file
             // int wc=wait(NULL);
             printf("child2,pid:%d\n",getpid());
             char buf[]= "12345";
             // 写入pipe
             if(write(fds[1],buf,sizeof(buf))!=sizeof(buf))
             {
                 perror("write to pipe");
                 exit(1);
             }
             exit(0);
         }
     }

     return 0;
 }
