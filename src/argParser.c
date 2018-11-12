

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

enum options { NAME , EXEC , PRINT , L, I , T};


#define OPTIONS_NUMBER 6

typedef	struct{
	int flags[6];
	char* path;
	char* name;
	char* exec;
	char* text;
	int hasPath;
} args;


void getArgs(args* myArgs,int argc,char* argv[]){
	
	//NE PAS OUBLIER D'INITIALISER
	memset(myArgs,0,sizeof(args));
	
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
				myArgs->flags[NAME]=1;
				myArgs->name=optarg;
				cntOpt +=2;
				break;
			case 'e':
				myArgs->flags[EXEC]=1;
				myArgs->exec=optarg;
				cntOpt +=2;
				break;
			case 'p':
				myArgs->flags[PRINT]=1;
				cntOpt +=1;
				break;
			case 'l':
				myArgs->flags[L]=1;
				cntOpt +=1;
				break;
			case 'i':
				myArgs->flags[I]=1;
				cntOpt +=1;
				break;
			case 't':
				myArgs->flags[T]=1;
				myArgs->text=optarg;
				cntOpt +=2;
				break;
			case '?':
				printf("L'option n'est pas reconnue\n");
				cntOpt +=1;
				break;

			default:
				printf("L'option n'est pas reconnue\n");
				break;
		}
	}

	if((argc-cntOpt)!=0){
		myArgs->hasPath = 1;
	}
}