#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <string.h>
#include "argParser.c"
#include <errno.h>

#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>


void affichage(char* path);

void lsDir(char* path,char* name){
	
	
	struct stat path_stat;
	memset(&path_stat,0,sizeof(path_stat));
    stat(path, &path_stat);
	
	
	//cas de base
	if(myArgs.flags[NAME]){
		//--name CHAINE
		//if filename == CHAINE : display
		if(name!= NULL && !strcmp(name,myArgs.name)){
			affichage(path);
		}
	}
	else if(myArgs.flags[T]){

		if(S_ISREG(path_stat.st_mode)){
			
			int fd;
			fd = open(path,O_RDONLY);
			stat(path,&path_stat);
			char fileBuffer[path_stat.st_size];
			read(fd,fileBuffer,path_stat.st_size);

			if(strstr(fileBuffer,myArgs.text)!=NULL){
				affichage(path);
			}
		}
	}
	else{
		// Affichage par defaut sans options
		affichage(path);	
	}
	
	
	
	//appel recursif
	if(S_ISDIR(path_stat.st_mode)){
		
		DIR* dp;			//directory to list		
		struct dirent *ep;	//curent file being listed
		dp=opendir(path);
		
		if(dp!=NULL){
			
			while((ep=readdir(dp))!=NULL){
			
				//if it is not current dir or parent dir
				if(strcmp(ep->d_name,".git")&& strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){

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
			return 1;
		}		
	}
}



void affichage(char* path){
	if(!myArgs.flags[L]){
		printf("%s\n",path);
	}
	else{
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
}
