#include <unistd.h>
#include <stdio.h>
#include "listbis.c"



int main(int argc,char** argv){

	getArgs(argc,argv);
	lsDir(myArgs.path,NULL);
	return 0;
}

