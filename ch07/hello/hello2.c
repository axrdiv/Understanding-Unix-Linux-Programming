/* hello2.c
 * purpose: show how to use curses functions with a loop
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
    }
    refresh();                      /* update the screen */
    getch();                        /* wait for user input */
    endwin();                       /* reset the tty mode */

    return 0;
}
