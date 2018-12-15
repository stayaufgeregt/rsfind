#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_

#include "structures.h"

command_t str2cmd(char*);			//converts a pipe separated string into a command_t (char** argv)
statement_t parseCmd(char*);		//converts a string --exec command into a statement_t (command_t* with metadata)
void free_command(command_t);		//frees memory allocated to command_t
void free_statement(statement_t);	//frees memory taken by statement_t, frees individually every command_t


#endif