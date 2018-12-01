#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#define DEBUG 1

enum options { NAME , EXEC , PRINT , L, I , T};

#define OPTIONS_NUMBER 6

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
}args_t;




#endif