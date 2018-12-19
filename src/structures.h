#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <stddef.h>
#include "dynamic_array.h"

#define DEBUG 0

///different options
enum options { _name , _exec , _print , _l, _i , _t, _ename, _T, _p};

#define OPTIONS_NUMBER 9

///file descriptors for a pipe
typedef struct{
	int fd[2];
}pipe_t;


///represents a simple command without pipes, each entry of argv is a space separated word, argv ends with NULL
typedef struct{
	char** argv;
}command_t;

///represents the complete command of --exec, i.e. simple commands separated by pipes
typedef struct{
	
	///location of the brackets in subCommands
	size_t bracketsPos[2];
	///array containing the parsed --exec string command
	command_t* subCommands;
	///number of elements of subCommands
	size_t size;
}statement_t;

///represents the arguments passed to rsfind
typedef	struct{
	///flag[option]=1 if this option is an argument of rsfind
	int flags[OPTIONS_NUMBER];
	statement_t exec;
	char* path;
	char* name;
	char* text;
	char* ename;
	char* T;
	int nthreads;
}args_t;

///global variable for the program's options
args_t myArgs;
///global variable to store the files to process later
dynamic_array* filesFound;

#endif