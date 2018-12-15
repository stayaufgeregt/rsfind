#ifndef DISPLAY_H_
#define DISPLAY_H_

void simpleDisplay(char* path){
	printf("%s\n",path);
	fflush(stdout);
}
void detailedDisplay(char* path){
	struct stat path_stat;	//info about the file
	struct group *info_gp;	//info about file's gid
	struct passwd *info_usr;//info about file's uid

	stat(path,&path_stat);
	(path_stat.st_mode & S_IFDIR)?(printf("d")):(printf("-"));
	(path_stat.st_mode & S_IRUSR)?(printf("r")):(printf("-"));
	(path_stat.st_mode & S_IWUSR)?(printf("w")):(printf("-"));
	(path_stat.st_mode & S_IXUSR)?(printf("x")):(printf("-"));
	(path_stat.st_mode & S_IRGRP)?(printf("r")):(printf("-"));
	(path_stat.st_mode & S_IWGRP)?(printf("w")):(printf("-"));
	(path_stat.st_mode & S_IXGRP)?(printf("x")):(printf("-"));
	(path_stat.st_mode & S_IROTH)?(printf("r")):(printf("-"));
	(path_stat.st_mode & S_IWOTH)?(printf("w")):(printf("-"));
	(path_stat.st_mode & S_IXOTH)?(printf("x")):(printf("-"));
	printf(" %d",(int)path_stat.st_nlink);

	info_usr=getpwuid(path_stat.st_uid);
	printf(" %s",info_usr->pw_name);

	info_gp=getgrgid(path_stat.st_gid);
	printf(" %s",info_gp->gr_name);

	printf(" %ld",(unsigned long)path_stat.st_size);

	struct tm t;
	localtime_r(&path_stat.st_mtime,&t);
    char str_time[24];
    strftime(str_time, sizeof(str_time), "%b %-2d %H:%M", &t);
    printf(" %s", str_time);
	
	printf(" %s\n",path);
	fflush(stdout);
}

#endif