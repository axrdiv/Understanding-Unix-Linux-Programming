/* hello3.c
 * purpose: using refresh and sleep for animated effects
 * outline: ininialize, draw stuff, wrap up
 */
#include<stdio.h>
#include<curses.h>

int main() {
    int i;
    initscr();                      /* turn on curses */
    clear();                        /* clear screen */
    for(i = 0; i < LINES; i++) {    /* in a loop */
        move(i, i + 1);
        if(i & 1)
            standout();
        addstr("Hello, world");
        if(i & 1)
            standend();
        sleep(1);
        refresh();                  /* update the screen */
    }
    endwin();                       /* reset the tty mode */

    return 0;
}
