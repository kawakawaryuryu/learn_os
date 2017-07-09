#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

    int rc = fork();

    char *env[3];
    env[0] = NULL; 
    env[1] = NULL;

    char *arg[5];
    arg[0] = "";
    arg[1] = "-l";
    arg[2] = NULL;

    //execl("/bin/ls", "/bin/ls", "-l", NULL);
    //execle("/bin/ls", "/bin/ls", "-l", NULL, env);
    //execlp("ls", "", "-l", NULL);
    //execv("/bin/ls", arg);
    //execvp("ls", arg);
    execve("/bin/ls", arg, env);

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("I'm a child process (pid: %d)\n", getpid());
    } else {
        printf("I'm a parent process (rc: %d, pid: %d)\n", rc, getpid());
    }
}
