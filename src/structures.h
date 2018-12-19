#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <stddef.h>
#include "dynamic_array.h"

#define DEBUG 1

enum options { _name , _exec , _print , _l, _i , _t, _ename, _T, _p};

#define OPTIONS_NUMBER 9

typedef struct{
	int fd[2];
}pipe_t;

typedef struct{
	char** argv;
}command_t;

typedef struct{
	size_t bracketsPos[2];		//location of the "{}" in the command		
	command_t* subCommands;
	size_t size;
}statement_t;			//command with pipes parsed


typedef	struct{
	int flags[OPTIONS_NUMBER];
	statement_t exec;
	char* path;
	char* name;
	char* text;
	char* ename;
	char* T;
	int nthreads;
}args_t;


args_t myArgs;
dynamic_array* filesFound;

#endif