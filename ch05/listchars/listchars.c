/* listchars.c
 * purpose: list individuall all the chars seen on input
 *  output: char and ascii code, one pair per line
 *   input: stdin, until the letter Q
 *   notes: usesful to show that buffering/editing exits
 */
#include<stdio.h>

int main() {
    int c, n = 0;
    while((c = getchar()) != 'Q')
        printf("char %3d is %c code %d\n", n++, c, c);

    return 0;
}
