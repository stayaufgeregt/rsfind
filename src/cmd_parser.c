#include <stdlib.h>
#include <string.h>

#include "structures.h"

command_t str2cmd(char*);
statement_t parseCmd(char*);
void free_command(command_t);
void free_statement(statement_t);
void free_args(args_t);

statement_t parseCmd(char* execCommand){
	//splits a command under string format into subcommands separated by pipes
	statement_t exec;

	exec.subCommands=malloc(sizeof(command_t)*strlen(execCommand));	//at most strlen pipes, realloc later
	exec.size = 0;
	
	char* savePtr;
	char* curSubCommand = strtok_r(execCommand,"|",&savePtr);
	
	while(curSubCommand!=NULL){
		exec.subCommands[exec.size]=str2cmd(curSubCommand);
		curSubCommand = strtok_r(NULL,"|",&savePtr);
		exec.size++;
	}

	exec.subCommands=realloc(exec.subCommands,sizeof(command_t)*exec.size);
	
	//find the position of the filename to be inserted to avoid later calculations
	char* bracketsPosition=NULL;
	
	for(size_t commandId=0; commandId<exec.size; commandId++){
		
		for(size_t wordId=0;exec.subCommands[commandId].argv[wordId]!=NULL; wordId++){
			bracketsPosition=strstr(exec.subCommands[commandId].argv[wordId],"{}");
			if(bracketsPosition!=NULL){
				//replace "{}" by %s
				bracketsPosition[0]='%';
				bracketsPosition[1]='s';
				//remember position of the word
				exec.bracketsPos[0]=commandId;
				exec.bracketsPos[1]=wordId;
				goto done;
			}
		}
	}
	printf("No brackets founds.\n");
	exit(EXIT_FAILURE);
	
	done:
	
	return exec;
}


command_t str2cmd(char* str_cmd){
	//splits a pipeless command into a list of space separated words.

	command_t cmd;
	
	cmd.argv=malloc(sizeof(char*)*strlen(str_cmd));
	size_t nbWords=0;
	
	char* curWord=strtok(str_cmd," ");
	
	while(curWord!=NULL){
		cmd.argv[nbWords]=curWord;
		curWord = strtok(NULL," ");
		nbWords++;
	}
	cmd.argv[nbWords]=NULL;
	cmd.argv=realloc(cmd.argv,sizeof(char*)*(nbWords+1));
	
	return cmd;
}

void free_command(command_t c){
	free(c.argv);
}

void free_statement(statement_t s){
	
	for(size_t i=0; i<s.size; i++){
		free_command(s.subCommands[i]);
	}
	free(s.subCommands);
}

void free_args(args_t a){
	free(a.execstr);
	free_statement(a.exec);
}