/* logout_tty(char *line)
 * marks a utmp record as logged out
 * does not blank username or remote host
 * return -1 on error, 0 on success
 *
 * function is in the tail of file
 */

#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST                    /* include remote machine on output */

void show_info(struct utmp *);

int main() {
    struct utmp * utbufp,           /* holds pointer to next rec */
                * utmp_next();      /* returns pointer to next */

    if(utmp_open(UTMP_FILE) == -1) {
        perror(UTMP_FILE);          /* UTMP_FILE is in utmp.h */
        exit(1);
    }

    while((utbufp = utmp_next()) != ((struct utmp *)NULL))
        show_info(utbufp);

    utmp_close();
    return 0;                       /* went ok */

    return 0;
}

/*
 * show_info()
 * displays contents of the utmp struct in human readable form
 * *note* these sizes should not be hardwired
 */
void show_info(struct utmp *utbufp) {
    if(utbufp->ut_type != USER_PROCESS)                     /* users only */
        return;

    printf("%-8.8s", utbufp->ut_name);                      /* the logname */
    printf(" ");                                            /* a space */
    printf("%-8.8s", utbufp->ut_line);                      /* the tty */
    printf(" ");                                            /* a space */
    printf("%12.12s", ctime(&(utbufp->ut_time)) + 4);       /* login time */
    printf(" ");                                            /* a space */
#ifdef SHOWHOST
    if(utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);                    /* the host */
#endif
    printf("\n");
}

int logout_tty(char * line) {
    int         fd;
    struct utmp rec;
    int         len = sizeof(struct utmp);
    int         retval = -1;                        /* pessimism */

    if((fd = open(UTMP_FILE, O_RDONLY)) == -1)      /* open file */
        return -1;
    /* search and replace */
    while(read(fd, &rec, len) == len)
        if(strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0) {
            rec.ut_type = DEAD_PROCESS;             /* set type */
            if(time(&rec.ut_time != -1))            /* and time */
                if(lseek(fd, -len, SEEK_CUR) != -1) /* back up */
                    if(write(fd, &rec, len) == len) /* update */
                        retval = 0;                 /* success! */
            break;
        }
    /* close the file */
    if(close(fd) == -1)
        retval = -1;
    return retval;
}
