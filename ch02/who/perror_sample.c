#include<stdio.h>
#include<fcntl.h>

int main() {
    int fd;
    fd = open("file", O_RDONLY);
    if(fd == -1) {
        perror("Cannot open file");
        return 0;
    }
    return 0;
}
