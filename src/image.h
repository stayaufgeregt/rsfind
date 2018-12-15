#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <magic.h>
#include <string.h>


struct{
	void* handle;
	magic_t (*open)(int);
	int (*load)(magic_t,const char*);
	void (*close)(magic_t);
	const char * (*file)(magic_t,const char*);
}magic;

void load_magic(){
	magic.handle=dlopen("libmagic.so.1",RTLD_LAZY);

	magic.open=dlsym(magic.handle,"magic_open");
	magic.load=dlsym(magic.handle,"magic_load");
	magic.close=dlsym(magic.handle,"magic_close");
	magic.file=dlsym(magic.handle,"magic_file");

	if (!magic.handle) {
	   fprintf(stderr, "%s\n", dlerror());
	   exit(EXIT_FAILURE);
	}
	dlerror();
	
	magic.handle=dlopen("libmagic.so.1",RTLD_LAZY);
	magic.open=dlsym(magic.handle,"magic_open");
	magic.load=dlsym(magic.handle,"magic_load");
	magic.close=dlsym(magic.handle,"magic_close");
	magic.file=dlsym(magic.handle,"magic_file");

	if (!magic.handle) {
	   fprintf(stderr, "%s\n", dlerror());
	   exit(EXIT_FAILURE);
	}
	dlerror();
}

void close_magic(){
	dlclose(magic.handle);
}

bool isImage(char* path){//true if file is an image; regardless of its extension
	
	const char *magic_info;
	magic_t magic_buf=magic.open(MAGIC_MIME_TYPE);

	if (magic.load(magic_buf, NULL) != 0) {
		magic.close(magic_buf);
		exit(1);
	}
	magic_info=magic.file(magic_buf, path);
	return strncmp("image",magic_info,5)==0;
}

#endif