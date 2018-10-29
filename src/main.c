#include <unistd.h>
#include <stdio.h>
#include "listDir.c"

int main(int argc,char* argv[]){

	args mesArgs;
	getArgs(&mesArgs,argc,argv);

	if(argc<2){
		char currentPath[2]=".";
		mesArgs.path=currentPath;//vérifier
	}
	else{
		mesArgs.path=argv[argc-1];//vérifier
	}
	//printf("%s\n",mesArgs.path);
	lsDir(mesArgs.path,&mesArgs);

}
