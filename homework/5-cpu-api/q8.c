#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) {

    int pipefd[2];
    pipe(pipefd);

    int rc1 = fork();
    int rc2 = fork();

    char buf;

    if (rc1 < 0 || rc2 < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc1 > 0 && rc2 > 0) {
        //int wc = wait(NULL);
        printf("We are parent processes (rc1: %d, rc2: %d, pid: %d)\n", rc1, rc2, getpid());
    } else if (rc1 > 0 && rc2 == 0) {
        printf("I'm parent and child processes (rc1: %d, rc2: %d, pid: %d)\n", rc1, rc2, getpid());
        write(pipefd[1], "HHHH\n", 5);
        close(pipefd[1]);
    } else if (rc1 == 0 && rc2 > 0) {
        printf("I'm a child and parent process (rc1: %d, rc2: %d, pid: %d)\n", rc1, rc2, getpid());

        while(read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
    } else if (rc1 == 0 && rc2 == 0) {
        printf("We are child processes (rc1: %d, rc2: %d, pid: %d)\n", rc1, rc2, getpid());
    } else {
        fprintf(stderr, "amazing!\n");
    }

}
