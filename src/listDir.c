#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "argParser.c"
#include <errno.h>

void lsDir(char* path,args* mesArgs){


	DIR* dp;
	//represents directory to list
	struct dirent *ep;
	//file

	dp=opendir(path);
	
	printf("%s\n",path);
	if(dp!=NULL){

		//while there is a file to read
		while((ep=readdir(dp))!=NULL){

			//d_name == filename
			if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){

				if(mesArgs->flags[NAME]){
					if(!strcmp(ep->d_name,mesArgs->name))
						printf("%s%s\n",path,ep->d_name);
				}
				else{
					printf("%s%s\n",path,ep->d_name);
				}

				printf("Fichier %s, type %d\n",ep->d_name,ep->d_type);
				if(ep->d_type==DT_DIR){
					/*char* childPath=malloc(sizeof(char)*(strlen(ep->d_name)+4));
					childPath[0]='.';
					childPath[1]='/';
					childPath[2]='\0';*/
					char childPath[strlen(ep->d_name)+4];
					strcpy(childPath,"./");
					strcat(childPath,ep->d_name);
					strcat(childPath,"/");

					

					lsDir(childPath,mesArgs);
				}
			}
		}
		closedir(dp);
	}
	else{
		printf("Couldn't open directory %d\n",errno);
	}
}