#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void) {

    int fd = open("./q2file.txt", O_CREAT|O_WRONLY, S_IRWXU);
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("I'm a child process (pid: %d)\n", getpid());
        write(fd, "11", 2);
        close(fd);
    } else {
        printf("I'm a parent process (rc: %d, pid: %d)\n", rc, getpid());
        write(fd, "22", 2);
        close(fd);
    }
}
