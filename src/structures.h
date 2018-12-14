#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#define DEBUG 1

enum options { _name , _exec , _print , _l, _i , _t, _ename, _T, _p};

#define OPTIONS_NUMBER 9

typedef struct{
	char** argv;
}command_t;

typedef struct{
	command_t* subCommands;
	size_t size;
}statement_t;


typedef	struct{
	int flags[OPTIONS_NUMBER];
	statement_t exec;
	char* execstr;
	char* path;
	char* name;
	char* text;
	char* ename;
	char* T;
	int nthreads;
}args_t;




#endif