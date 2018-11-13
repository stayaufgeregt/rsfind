#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "argParser.c"
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>

char* findChild(char* path,struct dirent* ep){
	char* childPath=malloc(sizeof(char)*(strlen(path)+1+strlen(ep->d_name)));
		strcpy(childPath,path);
		strcat(childPath,"/");
		strcat(childPath,ep->d_name);
		// on fabrique le chemin fils "pathPere/nomFichierFils"	
	return childPath;

}

void affichageList(char* path){

	struct stat path_stat;
	//info about the file

	struct group *info_gp;
	//info about file's gid

	struct passwd *info_usr;
	//info about file's uid

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

void lsDir(char* path,args* myArgs){

	DIR* dp;
	//directory to list
	
	struct dirent *ep;
	//curent file being listed

	struct stat path_stat;
	//info about the file

	static int start=1;

	dp=opendir(path);
	
	if((strcmp(path,".")==0) && !myArgs->flags[L] && !myArgs->flags[T]){
		printf("%s\n",path);
	}
	//affichage du repertoire courant une seule fois

	//if directory is open
	if(dp!=NULL){

	
		//while there is a file to read
		while((ep=readdir(dp))!=NULL){
			
			//d_name == filename
			
			//if it is not current dir or parent dir
			if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){

				char *childPath=findChild(path,ep);

				if(myArgs->flags[L]){

					if(strcmp(path,myArgs->path)==0 && start){
						start = 0;
						affichageList(path);
					}
					affichageList(childPath);

					if(ep->d_type==DT_DIR){
						lsDir(childPath,myArgs);
					}

				} else if(myArgs->flags[NAME]){
					//--name CHAINE
					//if filename == CHAINE : display
					
					if(!strcmp(ep->d_name,myArgs->name)){
						printf("%s\n",childPath);
					}

				} else if(myArgs->flags[T]){
					
					if(ep->d_type==DT_REG){
						int fd;
						fd = open(childPath,O_RDONLY);
						stat(childPath,&path_stat);
						char fileBuffer[path_stat.st_size];
						read(fd,fileBuffer,path_stat.st_size);
		
						if(strstr(fileBuffer,myArgs->text)!=NULL){
							printf("%s\n",childPath);
						}


					} else if(ep->d_type==DT_DIR){
						lsDir(childPath,myArgs);
					}
					

				} else {
					// Affichage par defaut sans options
					printf("%s\n",childPath);

						if(ep->d_type==DT_DIR){
							lsDir(childPath,myArgs);
						}

				}
			//free(childPath);
			}
		}
		closedir(dp);
	}
	else{
		printf("Couldn't open directory, error : %d.\n",errno);
	}
}
