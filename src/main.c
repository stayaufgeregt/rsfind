#include <unistd.h>
#include <stdio.h>
#include "listDir.c"

int main(int argc,char* argv[]){

	args myArgs;
	getArgs(&myArgs,argc,argv);

	if(argc<2){ //Si sans options
		char currentPath[2]=".";
		myArgs.path=currentPath;
	}
	else{
		if(myArgs.hasPath){
			myArgs.path=argv[argc-1];
			printf("%s",myArgs.path);
		} else {
			myArgs.path=".";
		}
	}
	//printf("%s\n",myaRgs.path);
	lsDir(myArgs.path,&myArgs);

}
