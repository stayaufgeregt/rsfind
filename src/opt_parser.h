#ifndef OPT_PARSER_H_
#define OPT_PARSER_H_

#include "structures.h"
void free_args(args_t a);				//frees arg_t struct declared in structures.h
void getArgs(int argc,char* argv[]);	//parses program argv to fill arg_t struct

#endif