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
#include <stdbool.h>

#include "exec.c"
#include "regex_matcher.c"
#include "opt_parser.c"
#include "sugar.h"

void applyAction(char* filePath);		//--print, --exec or ls -l on the current file
bool hasName(char* fileName);			//fileName==CHAINE with --name CHAINE 
bool hasText(char* filePath,struct stat* fileStat);		//file located at filePath contains string CHAINE with -t CHAINE
void recursiveSearch(char* filePath,char* fileName);	//in-depth search from filePath
//fileName is contained in filePath but it avoids some processing to pass it as an argument.



void recursiveSearch(char* path,char* name){
	
	struct stat path_stat;
	memset(&path_stat,0,sizeof(path_stat));
    stat(path, &path_stat);
	

	if( (!myArgs.flags[_name] 	|| hasName(name) ) &&
		(!myArgs.flags[_t]	 	|| hasText(path,&path_stat) ) &&
		(!myArgs.flags[_i] 	 	|| isImage(path) ) &&
		(!myArgs.flags[_ename]	|| regexNameMatch(path) ) &&
		(!myArgs.flags[_T]		|| regexTextMatch(path) ))
		push_back_cpy(filesFound,path);

		//applyAction(path);
	
	//recursive call if the file is a directory
	if(S_ISDIR(path_stat.st_mode)){
		
		DIR* dp;			//directory to list		
		struct dirent *ep;	//current file being listed
		dp=opendir(path);
		
		if(dp!=NULL){
			
			while((ep=readdir(dp))!=NULL){
			
				//if it is not current dir or parent dir
				if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){
					
					//creation of the child's path
					char *childPath;
					size_t path_len=strlen(path);
					if(path[path_len-1]=='/')	//avoid excedent '/' when parameter is "DOSSIER/+"
						path_len--;
					childPath=malloc(sizeof(char)*(path_len+strlen(ep->d_name)+2));
					strncpy(childPath,path,path_len);
					childPath[path_len]='\0';
					strcat(childPath,"/");
					strcat(childPath,ep->d_name);		
					
					recursiveSearch(childPath,ep->d_name);
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



void applyAction(char* path){

	if(myArgs.flags[_exec]){
		
		
		
		#ifdef DEBUG
		//system(command);
		/*for(size_t commandId=0; commandId<EXEC_SIZE; commandId++){
			for(size_t wordId=0;STATEMENT(commandId,wordId)!=NULL; wordId++){
				printf("%s ",STATEMENT(commandId,wordId));
			}
			printf("\n");
		}*/
		exec(path);
		
		#else
		// parse the command

		#endif

		
	}
	else if(myArgs.flags[_l]){
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

		char* tmp = ctime(&path_stat.st_mtime);
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
