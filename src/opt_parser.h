#ifndef OPT_PARSER_H_
#define OPT_PARSER_H_

#include "structures.h"

///frees memory allocated to arg_t structure
void free_args(args_t a);
///parses program char** argv to fill arg_t myArgs global structure
void getArgs(int argc,char* argv[]);

#endif