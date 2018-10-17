#include <unistd.h>
#include <stdio.h>
#include "listDir.c"

int main(int argc,char* argv[]){

	args mesArgs;
	mesArgs.path=argv[argc-1];//vérifier
	getArgs(&mesArgs,argc,argv);
	//printf("%s\n",mesArgs.path);
	lsDir(mesArgs.path,&mesArgs);

}
