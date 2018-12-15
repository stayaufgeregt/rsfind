#include "opt_parser.c"
#include "rsfind.c"


int main(int argc,char** argv){
	
	
	getArgs(argc,argv);
	filesFound=new_dynamic_array();
	
	recursiveSearch(myArgs.path,NULL);
	
	if(myArgs.flags[_i])
		close_magic();
	
	for(size_t i=0;i<size(filesFound); i++)
		applyAction(at(filesFound,i));
	
	free_strings(filesFound);
	free_dynamic_array(filesFound);
	free_args(myArgs);
	return 0;
}

