#include<stdio.h>
#include<unistd.h>

int main(void) {

    int x = 0;
    int rc = fork();

    if (rc < 0) {
    
    } else if (rc == 0) {
        printf("I'm a child process (pid: %d), x = %d\n", getpid(), x);
    } else {
        x = 100;
        printf("I'm a parent process (rc: %d, pid: %d), x = %d\n", rc, getpid(), x);
    }
}
