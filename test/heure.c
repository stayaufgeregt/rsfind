#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

int main() {
	struct stat path_stat;
	stat("./kaid.c",&path_stat);
    struct tm t;
	localtime_r(&path_stat.st_mtime,&t);
    char s[32];
    strftime(s, sizeof(s), "%b %d %H:%M", &t);
    printf("%s\n", s);
}