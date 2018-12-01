#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "cmd_parser.c"

static args_t myArgs;


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
		{"print",no_argument,NULL,'p'}
	};

	
	while((opt=getopt_long(argc,argv,"n:e:plit:",long_options,&option_index))!=-1){
		
		switch((char)opt){

			case 'n':
				myArgs.flags[NAME]=1;
				myArgs.name=optarg;
				cntOpt +=2;
				break;
			case 'e':
				myArgs.flags[EXEC]=1;
				cntOpt +=2;
				
				//replace {} with %s
				char* bracketsPosition=strstr(optarg,"{}");
				if(bracketsPosition==NULL)exit(1);
				strncpy(bracketsPosition,"%s",2);
				
				myArgs.execstr=malloc(sizeof(char)*strlen(optarg));
				strncpy(myArgs.execstr,optarg,strlen(optarg));
				myArgs.exec=parseCmd(optarg);
				break;
			case 'p':
				myArgs.flags[PRINT]=1;
				cntOpt +=1;
				break;
			case 'l':
				myArgs.flags[L]=1;
				cntOpt +=1;
				break;
			case 'i':
				myArgs.flags[I]=1;
				cntOpt +=1;
				break;
			case 't':
				myArgs.flags[T]=1;
				myArgs.text=optarg;
				cntOpt +=2;
				break;
			case '?':
				printf("L'option n'est pas reconnue\n");
				cntOpt +=1;
				exit(1);
				break;

			default:
				printf("L'option n'est pas reconnue\n");
				exit(1);
				break;
		}
	}

	
	if((argc-cntOpt)!=0){
		//if path is provided; it is set at the end of argv by getopt
		myArgs.path=argv[argc-1];
	}
	else{
		//default path
		myArgs.path=".";
	}
	
}