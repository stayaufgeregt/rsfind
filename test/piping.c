#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NB_PIPES 2
typedef struct{
	int fd[2];
}pipe_t;
typedef char* string;
typedef struct{
	string argv[3];
}cmd_t;
int main(int argc, char *argv[])
{
	
	pipe_t* pipes=malloc(NB_PIPES*sizeof(pipe_t));
	int* pids=malloc((NB_PIPES+1)*sizeof(int));
	char buffer[256];
	buffer[0]='\0';
	char* commands[]={"cat","grep","grep"};
	char* params[]={"./piping.c","int","p"};
	cmd_t* m=malloc(3*sizeof(cmd_t));
	m[0].argv[0]=commands[0];
	m[0].argv[1]=params[0];
	m[0].argv[2]=NULL;
	
	m[1].argv[0]=commands[1];
	m[1].argv[1]=params[1];
	m[1].argv[2]=NULL;
	
	m[2].argv[0]=commands[2];
	m[2].argv[1]=params[2];
	m[2].argv[2]=NULL;
	
	for(int i=0; i<NB_PIPES+1; i++){
		
		if(i!=NB_PIPES){
			pipe(pipes[i].fd);
		}
		
		pids[i]=fork();
		
		if(pids[i]==0){
			printf("Salut : %s %s\n",commands[i],params[i]);fflush(stdout);
			if(i!=NB_PIPES){
				dup2(pipes[i].fd[1],1);
			}
			if(i!=0){
				dup2(pipes[i-1].fd[0],0);
				//read(0,buffer,256);
			}
			for(int j=0;j<NB_PIPES;j++){
				close(pipes[j].fd[0]);
				close(pipes[j].fd[1]);
			}
			execvp(m[i].argv[0],m[i].argv);
			
			exit(EXIT_SUCCESS);
		}
		else{
			//waitpid(pids[i],NULL,0);
		}
			
	}
	//fflush(stdout);
	//	for(int i=0;i<NB_PIPES;i++)
	wait(NULL);
}