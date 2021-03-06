#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "image.h"
#include "cmd_parser.h"
#include "opt_parser.h"

char DEFAULT_PATH[]=".";

void free_args(args_t a){
	free_statement(a.exec);
}

//analyses and processes the arguments passed to rsfind
//stores them in static structure myArgs
void getArgs(int argc,char* argv[]){
	
	//initialize
	memset(&myArgs,0,sizeof(myArgs));
	
	int opt;
	int option_index = 0;
	int cntOpt = 1;

	static struct option long_options[] ={
		{"name",required_argument,NULL,'n'},
		{"exec",required_argument,NULL,'e'},
		{"print",no_argument,NULL,'P'},
		{"ename",required_argument,NULL,'N'}
	};

	
	while((opt=getopt_long(argc,argv,"n:e:Plit:N:T:p:",long_options,&option_index))!=-1){
		
		switch((char)opt){

			case 'n':
				myArgs.flags[_name]=1;
				myArgs.name=optarg;
				cntOpt +=2;
				break;
			case 'e':
				myArgs.flags[_exec]=1;
				cntOpt +=2;
				myArgs.exec=parseCmd(optarg);
				break;
			case 'P':
				myArgs.flags[_print]=1;
				cntOpt +=1;
				break;
			case 'l':
				myArgs.flags[_l]=1;
				cntOpt +=1;
				break;
			case 'i':
				myArgs.flags[_i]=1;
				cntOpt +=1;
				load_magic();
				
				break;
			case 't':
				myArgs.flags[_t]=1;
				myArgs.text=optarg;
				cntOpt +=2;
				break;
			case 'N':
				myArgs.flags[_ename]=1;
				myArgs.ename=optarg;
				cntOpt+=2;
				break;
			case 'T':
				myArgs.flags[_T]=1;
				myArgs.T=optarg;
				cntOpt+=2;
				break;
			case 'p':
				myArgs.flags[_p]=1;
				myArgs.nthreads=atoi(optarg);
				cntOpt+=2;
				break;
			case '?':
				exit(EXIT_FAILURE);
				break;

			default:
				exit(EXIT_FAILURE);
				break;
		}
	}

	
	if((argc-cntOpt)!=0){
		//if path is provided; it is set at the end of argv by getopt
		myArgs.path=argv[argc-1];
	}
	else{
		myArgs.path=DEFAULT_PATH;
	}
	
}
