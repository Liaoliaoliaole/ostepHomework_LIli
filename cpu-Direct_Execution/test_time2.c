
#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
#include<fcntl.h>//for open()
#include<stdlib.h>
 
int main()
{
	//The argument flags must include one of the following access
        //modes: O_RDONLY, O_WRONLY, or O_RDWR.  These request opening the
        //file read-only, write-only, or read/write, respectively.
	int fd = open("./test_time2.c", O_RDONLY);
	int i;
	char buf[10];
	struct timeval start, end;
	if(fd == -1) {
		fprintf(stderr, "file open failed!\n");
		exit(1);
	}
	for(i=0;i<10;++i) {
		gettimeofday(&start, NULL);
		//read() attempts to read up to count bytes from file descriptor
		// fd into the buffer starting at buf.
		//ssize_t read(int fd, void *buf, size_t count)
		read(fd, buf, 0);//read 0 byte
		gettimeofday(&end, NULL);
		printf("%ld\n", end.tv_usec - start.tv_usec);
	}
	close(fd);
	return 0;

}
