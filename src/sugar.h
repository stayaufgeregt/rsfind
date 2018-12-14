#ifndef SUGAR_H_
#define SUGAR_H_


#define BRK_CMD myArgs.exec.bracketsPos[0]
#define BRK_WORD myArgs.exec.bracketsPos[1]
#define STATEMENT(command,word) myArgs.exec.subCommands[command].argv[word]
#define EXEC_SIZE myArgs.exec.size
#define PIPE_NUMBER EXEC_SIZE-1

#endif