#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void) {

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("hello\n");
    } else {
        sleep(1);
        printf("goodbye\n");
    }
}
