#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_
///@file
#include "structures.h"

///parses a string into a space-separated words
command_t str2cmd(char*);
///parses a string into a pipe-separated command_t
statement_t parseCmd(char*);
///frees memory allocated to command_t
void free_command(command_t);
///frees memory allocated to statement_t, frees individually every command_t
void free_statement(statement_t);


#endif