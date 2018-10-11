#include <unistd.h>
#include <stdio.h>
#include "argParser.c"


int main(int argc,char* argv[]){

	args mesArgs;
	getArgs(&mesArgs,argc,argv);
	printf("%s\n",mesArgs.name);
	printf("%s\n",mesArgs.exec);
	printf("%s\n",mesArgs.text);

}
