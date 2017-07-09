#define _GNU_SOURCE
#define LOOP 10000000
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sched.h>
#include<errno.h>

int main(int argc, char **argv) {

    cpu_set_t cpu_set;

    CPU_ZERO(&cpu_set);
    CPU_SET(0, &cpu_set);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set) != 0) {

        perror("ERROR");

        return;
    }


    // pipe file discriptor
    // pipefd[0]: read
    // pipefd[1]: write
    int parent_pipefd[2];
    int child_pipefd[2];
    int time_pipefd[2];

    // create pipe for parent
    if (pipe(parent_pipefd) == -1) {
        perror("parent pipe error");

        close(parent_pipefd[0]);
        close(parent_pipefd[1]);
        return;
    }

    // create pipe for child
    if (pipe(child_pipefd) == -1) {
        perror("child pipe error");
        return;
    }

    // create pipe for measuring context switch time
    if (pipe(time_pipefd) == -1) {
        perror("time pipe error");
        return;
    }

    struct timeval start;
    struct timeval end;

    // fork
    int pid = fork();

    char buf;


    if (pid < 0) {
        // failed fork
        close(parent_pipefd[0]);
        close(parent_pipefd[1]);
        close(child_pipefd[0]);
        close(child_pipefd[1]);

    } else if (pid == 0) {
        // child process

        int i;
        for (i = 0; i < LOOP; i++) {
            read(parent_pipefd[0], &buf, 0);
            write(child_pipefd[1], &buf, 0);
        }
        gettimeofday(&end, NULL);

        write(time_pipefd[1], &end, sizeof(struct timeval));

    } else {
        // parent process
        gettimeofday(&start, NULL);

        int i;
        for (i = 0; i < LOOP; i++) {
            write(parent_pipefd[1], &buf, 0);
            read(child_pipefd[0], &buf, 0);
        }

        read(time_pipefd[0], &end, sizeof(struct timeval));

        double switch_time = ((end.tv_sec - start.tv_sec)*1000*1000 + (end.tv_usec - start.tv_usec)) / 1000.0;
        printf("context switch = %lf\n", switch_time / ((double)LOOP * 2));
    }

}
