/* sigdemo1.c   - shows how a signal handler works.
 *              - run this and press Ctrl-C a few times
 */

#include<stdio.h>
#include<signal.h>

int main() {
    void f(int);                    /* declare the handler */
    int i;
    signal(SIGINT, f);              /* install the handler */
    for(int i = 0; i < 5; i++) {    /* do something else */
        printf("hello\n");
        sleep(1);
    }
    return 0;
}

void f(int signum) {                /* this function is called */
    printf("OUCH!\n");
}
