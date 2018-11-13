#include <stdio.h>
#include <stdlib.h>
#include <magic.h>
#include <string.h>

int main(void){

//}

//int isImage(struct dirent* ep)


//{
    char *file_name = "txtimg.odt"; //ep->d_name;
    const char *magic_info;
    magic_t magic_buf;
    char* model ="image";

    magic_buf = magic_open(MAGIC_MIME_TYPE);

  if (magic_load(magic_buf, NULL) != 0) {
        magic_close(magic_buf);
        return 1;
    }
	
    magic_info = magic_file(magic_buf, file_name);
    printf("%s\n",magic_info );
    char tmp[strlen(magic_info)];
    strcpy(tmp,magic_info);
    tmp[5]='\0';

    if(strcmp(model,tmp)==0){
        printf("1\n");
    } else {
        printf("0\n");
    }


    magic_close(magic_buf);
    return 0;
}
