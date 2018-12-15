#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sugar.h"
#include "structures.h"

void exec(char* path){
	
	char* saveWordPtr=STATEMENT(BRK_CMD,BRK_WORD);
	char* replacementWord=malloc(sizeof(char)*strlen(saveWordPtr)+strlen(path)-1);
	STATEMENT(BRK_CMD,BRK_WORD)=replacementWord;
	sprintf(replacementWord,saveWordPtr,path);
	//replaces %s by the path of the file
	//keeps the addres to restore later
	
	
	pipe_t pipes[EXEC_SIZE-1];
	int pids[EXEC_SIZE];

	
	for(size_t i=0; i<EXEC_SIZE; i++){
		
		if(i!=EXEC_SIZE-1){
			pipe(pipes[i].fd);
		}
		
		pids[i]=fork();

		if(pids[i]==0){//child process

			if(i!=EXEC_SIZE-1){
				dup2(pipes[i].fd[1],1);
				close(pipes[i].fd[0]);
				close(pipes[i].fd[1]);
			}
			if(i!=0){
				dup2(pipes[i-1].fd[0],0);
				close(pipes[i-1].fd[0]);
				close(pipes[i-1].fd[1]);
			}
			
			execvp(myArgs.exec.subCommands[i].argv[0],myArgs.exec.subCommands[i].argv);
			
			exit(EXIT_SUCCESS);
		}
		else{//parent process
			if(i!=EXEC_SIZE-1){
				close(pipes[i].fd[1]);
			}
			if(i!=0){
				close(pipes[i-1].fd[0]);
			}
		}
	}
	for(size_t i=0;i<EXEC_SIZE;i++)
		waitpid(pids[i],NULL,0);
	
	STATEMENT(BRK_CMD,BRK_WORD)=saveWordPtr;
	free(replacementWord);
}