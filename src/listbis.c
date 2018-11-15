#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>
#include <magic.h>
#include <stdbool.h>

#include "argParser.c"

void affichage(char* filePath);
bool hasName(char* fileName);
bool isImage(char* filePath);
bool hasText(char* filePath,struct stat* fileStat);
void lsDir(char* filePath,char* fileName);



void lsDir(char* path,char* name){
	
	
	struct stat path_stat;
	memset(&path_stat,0,sizeof(path_stat));
    stat(path, &path_stat);
	

	if( (!myArgs.flags[NAME] || hasName(name) ) &&
		(!myArgs.flags[T]	 || hasText(path,&path_stat) ) &&
		(!myArgs.flags[I] 	 || isImage(path) ) )
		
		affichage(path);
	
	//appel recursif
	if(S_ISDIR(path_stat.st_mode)){
		
		DIR* dp;			//directory to list		
		struct dirent *ep;	//curent file being listed
		dp=opendir(path);
		
		if(dp!=NULL){
			
			while((ep=readdir(dp))!=NULL){
			
				//if it is not current dir or parent dir
				if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){
					char *childPath=malloc(sizeof(char)*(strlen(path)+2+strlen(ep->d_name)));
					strcpy(childPath,path);
					strcat(childPath,"/");
					strcat(childPath,ep->d_name);
					lsDir(childPath,ep->d_name);
					free(childPath);
				}
			}
			closedir(dp);
		}
		else{
			exit(1);
		}		
	}
}


bool hasName(char* name){
	return name!=NULL && !strcmp(name,myArgs.name);
}

bool isImage(char* path){
	
	const char *magic_info;
	magic_t magic_buf=magic_open(MAGIC_MIME_TYPE);

	if (magic_load(magic_buf, NULL) != 0) {
		magic_close(magic_buf);
		exit(1);
	}
	magic_info=magic_file(magic_buf, path);
	return strncmp("image",magic_info,5)==0;
}

bool hasText(char* path,struct stat* path_stat){
	
	if(!S_ISREG(path_stat->st_mode))
		return false;
	
	int fd;
	fd = open(path,O_RDONLY);
	char fileBuffer[path_stat->st_size];
	read(fd,fileBuffer,path_stat->st_size);
	/////////////if read fails ????
	return strstr(fileBuffer,myArgs.text)!=NULL;
}


void affichage(char* path){

	if(myArgs.flags[EXEC]){
		pid_t pid;
		
		if((pid=fork())<0){
			exit(1);
		}
		else if(pid==0){
			char* command=malloc(sizeof(char)*strlen(myArgs.exec)+strlen(path)+1);
			
			sprintf(command,myArgs.exec,path);
			
			system(command);
			free(command);
			exit(0);
		}
		else{
			int statut;
			int options = 0;
			waitpid(pid, &statut, options);
		}
	}
	else if(myArgs.flags[L]){
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

	char* tmp = ctime(&path_stat.st_ctime);
	tmp = tmp + 4; // enlever le mois en toutes lettres
	tmp[strlen(tmp)-9]='\0';// enlever les secs et l'année
	tmp[0]=tmp[0]+32; // la maj du mos en min
	char* tmp2 = malloc(strlen(tmp)*sizeof(char));
	strcpy(tmp2,tmp);
	tmp[3]='\0';
	tmp2[1]='.';
	tmp2[2]=' ';
	tmp2 = tmp2 + 1;
	strcat(tmp,tmp2);
	
	printf(" %s",tmp);
	printf(" %s\n",path);
	//free(tmp2);
	}
	else{
		printf("%s\n",path);
	}
}
