
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

enum options { NAME , EXEC , PRINT , L, I , T};


#define OPTIONS_NUMBER 6

typedef	struct{
	int flags[OPTIONS_NUMBER];
	char* path;
	char* name;
	char* exec;
	char* text;
} args;

typedef struct{
	char** argv;
}command_t;

typedef struct{
	command_t* cmd;
	size_t nbCmd;
}statement_t;

statement_t parseCmd(char* command){
	char** tabStr=malloc(sizeof(char*)*strlen(command));
	int tabSize = 0;

	char* word = strtok(command,"|");
	while(word!=NULL){
		tabStr[tabSize]=word;
		word = strtok(NULL,"|");
		tabSize++;
	}
	tabStr[tabSize]=NULL;
	tabStr=realloc(tabStr,sizeof(char*)*(tabSize+1));
	for(int i=0;i<tabSize;i++){
		printf("%s\n",tabStr[i]);
	}
	printf("%d\n", tabSize);

	char ** tabCmd=malloc(sizeof(char*)*strlen(command));
	for(int j=0;j<tabSize;j++){
		word = strtok(tabStr[j]," ");

	}
	return 
}
static args myArgs;


//analyses and processes the arguments passed to rsfind
//stores them in static structure myArgs
void getArgs(int argc,char* argv[]){
	
	//initialize
	memset(&myArgs,0,sizeof(args));
	
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
				myArgs.exec=optarg;
				cntOpt +=2;
				
				//replace {} with %s
				char* bracketsPosition=strstr(myArgs.exec,"{}");
				if(bracketsPosition==NULL)exit(1);
				strncpy(bracketsPosition,"%s",2);
				
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