#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>

int main() {

    struct timeval start,end;

    gettimeofday(&start, NULL);
    sleep(5);
    gettimeofday(&end, NULL);

    printf("start = %ld\n", start.tv_sec);
    printf("start = %d\n", start.tv_usec);
    printf("end = %ld\n", end.tv_sec);
    printf("end = %d\n", end.tv_usec);

    printf("\nsleep = %ld.%d\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
}
