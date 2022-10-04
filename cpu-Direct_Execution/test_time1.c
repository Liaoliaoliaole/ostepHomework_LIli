//你将测量系统调用和上下文切换的成本。
//测量系统调用的成本相对容易,例如，你可以重复调用一个简单的系统调用并记下所花的时间。
//将时间除以迭代次数，就可以估计系统调用的成本。
//你必须考虑的一件事是时钟的精确性和准确性。
//你可以使用的典型时钟是gettimeofday()
//The gettimeofday() function gets the system’s clock time. 
//The current time is expressed in elapsed seconds and microseconds 
//int gettimeofday ( struct timeval *tp ,  struct timezone *tz )
//The 2nd argument points to the timezone structure. 
//It should normally be set to NULL because struct timezone is obsolete. 

#include <stdio.h>
#include <sys/time.h>

int main(){
	//struct timeval represents an elapsed time.(it includes 
	//time of seconds(tv_sec) and microseconds(tv_usec).)
	struct timeval start,end;
	int i;
	for(i=0; i<10; ++i) {
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		printf("%ld\n", end.tv_usec - start.tv_usec);
		printf("%ld %ld\n", end.tv_usec, start.tv_usec);
	}

	return 0;
}

