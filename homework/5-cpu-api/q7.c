#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]) {
 
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("I'm a child process (pid: %d)\n", getpid());
    } else {
        printf("I'm a parent process (rc: %d, pid: %d)\n", rc, getpid());
    }
}
