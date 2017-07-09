#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

    int N = 10000;
    int i;
    int sum = 0;

    for (i = 0; i < N; i++) {

        // system call前
        struct timeval tv_before;
        gettimeofday(&tv_before, NULL);

        // system call
        int fd;
        char buf;
        read(fd, &buf, 0);

        // system call後
        struct timeval tv_after;
        gettimeofday(&tv_after, NULL);

        sum += tv_after.tv_usec - tv_before.tv_usec;
    }

    printf("system call time = %lf\n", (double)sum / (double)N);
}
