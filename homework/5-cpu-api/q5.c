#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        int wcChild = wait(NULL);
        printf("I'm a child process (wc: %d, pid: %d)\n", wcChild, getpid());
    } else {
        int wc = wait(NULL);
        printf("I'm a parent process (rc: %d, wc: %d, pid: %d)\n", rc, wc, getpid());
    }
}
