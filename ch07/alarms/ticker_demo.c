/*
 * ticker_demo.c
 * demostrates use of interval timer to generate regular
 * signals, which are in turn caught and used to count down
 */

#include<stdio.h>
#include<sys/time.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

int set_ticker(int);

int main() {
    void countdown(int);
    signal(SIGALRM, countdown);
    if(set_ticker(500) == -1)
        perror("set_ticker");
    else
        while(1)
            pause();
    return 0;
}

void countdown(int signum) {
    static int num = 10;
    printf("%d..", num--);
    fflush(stdout);
    if(num < 0) {
        printf("DONE!\n");
        exit(0);
    }
}

