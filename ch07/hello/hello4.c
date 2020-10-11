/* hello4.c
 * purpose: show how to use erase, time, and draw for animation
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
        refresh();                  /* update the screen */
        sleep(1);
        move(i, i + 1);             /* move back */
        addstr("            ");     /* erase line */
    }
    endwin();                       /* reset the tty mode */

    return 0;
}
