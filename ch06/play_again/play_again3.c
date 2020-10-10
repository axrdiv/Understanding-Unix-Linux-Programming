/* play_again3.c
 * purpose: ask if user wants another transaction
 *  method: set tty into char-by-char mode,
 *          set tty into no-delay mode
 *          read char, return result
 * returns: 0=>yes, 1=>no
 *  better: reset terminal mode on Interrupt
 */
#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>

#define ASK         "Do you want another transaction"
#define TRIES       3                   /* max tries */
#define SLEEPTIME   2                   /* time per try */
#define BEEP        putchar('\a')       /* alert user */

int get_response(char *, int);
void tty_mode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
int get_ok_char();

int main() {
    int response;
    tty_mode(0);                            /* save current mode */
    set_cr_noecho_mode();                   /* set -icanon, -echo */
    set_nodelay_mode();                     /* noinput => EOF */
    response = get_response(ASK, TRIES);    /* get some answer */
    tty_mode(1);                            /* restore orig mode */
    return response;
}

int get_response(char *question, int maxtries)
/*
 * purpose: ask a question and wait for a y/n answer or maxtries
 *  method: use getchar and complain about non - y/n input
 * returns: 0=>yes, 1=>no, 2=>timeout
 */
{
    int input;
    printf("%s (y/n)? ", question);         /* ask */
    fflush(stdout);                         /* force output */
    while(1) {
        sleep(SLEEPTIME);                   /* wait a bit */
        input = tolower(get_ok_char());     /* get next chr */
        if(input == 'y')
            return 0;
        if(input == 'n')
            return 1;
        if(maxtries-- == 0)
            return 2;
    }
}

int get_ok_char() {
    int c;
    while((c = getchar()) != EOF && strchr("yYnN", c) == NULL)
        ;
    return c;
}

void set_cr_noecho_mode()
/*
 * purpose: put file descriptor 0 (i.e. stdin) into char-by-char mode
 *  method: use bits in termios
 */
{
    struct termios          ttystate;
    tcgetattr(0, &ttystate);            /* read curr.setting */
    ttystate.c_lflag    &=  ~ICANON;    /* no buffering */
    ttystate.c_lflag    &=  ~ECHO;      /* no echo either */
    ttystate.c_cc[VMIN] =   1;          /* get 1 char at a time */
    tcsetattr(0, TCSANOW, &ttystate);   /* install settings */
}

void set_nodelay_mode()
/*
 * purpose: put file descriptor 0 into no-delay mode
 *  method: use fcntl to set bit
 *   notes: tcsetattr() will do something similar, but it is complicated
 */
{
    int termflags;
    termflags = fcntl(0, F_GETFL);      /* read curr.settings */
    termflags |= O_NDELAY;              /* flip on nodelay bit */
    fcntl(0, F_SETFL, termflags);       /* and install 'em */
}



/* how == 0 => save current mode, how == 1 => restore mode */
void tty_mode(int how) {
    static struct termios original_mode;
    if(how == 0)
        tcgetattr(0, &original_mode);
    else
        tcsetattr(0, TCSANOW, &original_mode);
}