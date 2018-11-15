#include "rsfind.c"



int main(int argc,char** argv){

	getArgs(argc,argv);
	recursiveSearch(myArgs.path,NULL);
	return 0;
}

