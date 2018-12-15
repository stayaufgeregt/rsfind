#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdbool.h>
#include <magic.h>



struct{
	void* handle;
	magic_t (*open)(int);
	int (*load)(magic_t,const char*);
	void (*close)(magic_t);
	const char * (*file)(magic_t,const char*);
}magic;

bool isImage(char* path);//true if file is an image; regardless of its extension
void load_magic();		//dynamic load of libmagic
void close_magic();		//close magic handle

#endif