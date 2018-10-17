

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#define NAME 	0
#define EXEC 	1
#define PRINT 	2
#define L		3
#define I		4
#define T		5


typedef	struct{
	int flags[6];
	char* path;
	char* name;
	char* exec;
	char* text;
} args;

void getArgs(args* myArgs,int argc,char* argv[]){

	int opt;
	int option_index = 0;
	static struct option long_options[] ={
		{"name",required_argument,NULL,'n'},
		{"exec",required_argument,NULL,'e'},
		{"print",no_argument,NULL,'p'}
	};

	
	while((opt=getopt_long(argc,argv,"lit:",long_options,&option_index))!=-1){
		switch((char)opt){

			case 'n':
				myArgs->flags[NAME]=1;
				myArgs->name=optarg;
				break;
			case 'e':
				myArgs->flags[EXEC]=1;
				myArgs->exec=optarg;
				break;
			case 'p':
				myArgs->flags[PRINT]=1;
				break;
			case 'l':
				myArgs->flags[L]=1;
				break;
			case 'i':
				myArgs->flags[I]=1;
				break;
			case 't':
				myArgs->flags[T]=1;
				myArgs->text=optarg;
				break;

			default:
				printf("L'option n'est pas reconnue\n");
		}
	}
}