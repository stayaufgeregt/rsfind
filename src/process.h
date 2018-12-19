#ifndef THREADS_H_
#define THREADS_H_

/**
Applies operations on a path; namely --exec, --print, -l
*/
void applyAction(char*);
/**
Same as applyAction but with threads (not implemented yet)
*/
void* applyAction_thread(char* path);

#endif