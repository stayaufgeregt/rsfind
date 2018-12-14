#include <stdio.h>
/*#include <stdlib.h>
#include <dlfcn.h>
#include <magic.h>
*/
typedef struct{
	char subCommands;
	size_t bracketsPos[2];
	char size;
}t;
typedef struct{
	size_t bracketsPos[2];
	
	
	char size;
	char subCommands;
}p;
int main(void){
	printf("%lu, %lu",sizeof(t),sizeof(p));
   /*void *handlem;
   
   magic_t (*magic_open)(int);
   int (*magic_load)(magic_t,const char*);
   void (*magic_close)(magic_t);
   const char * (*magic_file)(magic_t,const char*);
   
   char *error;

   handlem= dlopen("libmagic.so.1",RTLD_LAZY);
   
   magic_open=dlsym(handlem,"magic_open");
   magic_load=dlsym(handlem,"magic_load");
   magic_close=dlsym(handlem,"magic_close");
   magic_file=dlsym(handlem,"magic_file");
   
   if (!handlem) {
	   fprintf(stderr, "%s\n", dlerror());
	   exit(EXIT_FAILURE);
   }

   dlerror(); 
	
	const char *magic_info;
	magic_t magic_buf=magic_open(MAGIC_MIME_TYPE);

	if (magic_load(magic_buf, NULL) != 0) {
		magic_close(magic_buf);
		exit(1);
	}
	magic_info=magic_file(magic_buf, "./kaid.c");
	printf("magic info : %s\n",magic_info);
    error = dlerror();
    if (error != NULL){
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

	dlclose(handlem);*/
	return 0;
}