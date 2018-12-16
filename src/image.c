#include "image.h"

#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>


void load_magic(){
	magic.handle=dlopen("libmagic.so.1",RTLD_LAZY);

	if (!magic.handle) {
	   exit(EXIT_FAILURE);
	}
	dlerror();

	magic.open=dlsym(magic.handle,"magic_open");
	magic.load=dlsym(magic.handle,"magic_load");
	magic.close=dlsym(magic.handle,"magic_close");
	magic.file=dlsym(magic.handle,"magic_file");

}

void close_magic(){
	dlclose(magic.handle);
}

bool isImage(char* path){//true if file is an image; regardless of its extension
	
	const char *magic_info;
	magic_t magic_buf=magic.open(MAGIC_MIME_TYPE);

	if (magic.load(magic_buf, NULL) != 0) {
		//UωU
		magic.close(magic_buf);
		exit(1);
	}
	magic_info=magic.file(magic_buf, path);

	bool a = strncmp("image",magic_info,5)==0;
	magic.close(magic_buf);

	return a;

}