#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "argParser.c"
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void lsDir(char* path,args* mesArgs){

	DIR* dp;
	//directory to list
	
	struct dirent *ep;
	//curent file being listed

	struct stat path_stat;
	dp=opendir(path);
	//printf("%s\n",path);

	//if we can open the directory
	if(dp!=NULL){

	
		//while there is a file to read
		while((ep=readdir(dp))!=NULL){
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
		printf(" %d",(int)path_stat.st_uid);
		printf(" %d",(int)path_stat.st_gid);
		printf(" %ld",(unsigned long)path_stat.st_size);
		char* tmp = ctime(&path_stat.st_ctime);
		tmp[strlen(tmp)-1]='\0';
		printf(" %s",tmp);
		printf("ici ICI %s\n",path);

		
			//d_name == filename
			//if it is not current dir or parent dir
			if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".") && strcmp(ep->d_name,".git")){

				
				
				
				//if the file is a directory : recursive call
				if(ep->d_type==DT_DIR){

					//display name of dir is done at the beginning of function
					char childPath[strlen(path)+strlen(ep->d_name)+2];
					strcpy(childPath,path);
					strcat(childPath,"/");
					strcat(childPath,ep->d_name);
					lsDir(childPath,mesArgs);
				}
				else{	
				//otherwise, display name
					
					if(mesArgs->flags[NAME]){
					//--name CHAINE
					//if filename == CHAINE : display
					printf("not supposed to be here\n");
						if(!strcmp(ep->d_name,mesArgs->name))
						printf("%s/%s\n",path,ep->d_name);
						}else{
							//default without options
							printf("LAAA%s/%s\n",path,ep->d_name);

					}
					
				}
			}
		}
		closedir(dp);
	}
	else{
		printf("Couldn't open directory, error : %d.\n",errno);
	}
}