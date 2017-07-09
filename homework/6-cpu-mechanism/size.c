#include<stdio.h>
#include<sys/time.h>

int main() {

    printf("time_t = %lu\n", sizeof(time_t));
    printf("long = %lu\n", sizeof(long));
    printf("suseconds_t = %lu\n", sizeof(suseconds_t));
    printf("int = %lu\n", sizeof(int));

}
