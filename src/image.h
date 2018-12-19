#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdbool.h>
#include <magic.h>


///global structure containing function pointers pointing to libmagic functions
struct{
	void* handle;
	magic_t (*open)(int);
	int (*load)(magic_t,const char*);
	void (*close)(magic_t);
	const char * (*file)(magic_t,const char*);
}magic;

///true if file is an image; false otherwise
bool isImage(char* path);
///dynamically load libmagic; fills global magic struct
void load_magic();
///closes libmagic
void close_magic();

#endif