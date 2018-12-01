#include "dynamic_array.h"
#include <stdio.h>
#include <string.h>

/*
int main(void){

	dynamic_array* filesFound=new_dynamic_array();
	char s[]="zbeuleur\n";
	for(int i=0;i<34;i++){
		printf("%d : ",i);fflush(stdout);
		push_back_cpy(filesFound,s);
		printf("result : %s",at(filesFound,(size_t)i));
	}
	printf("Le 4eme %s",filesFound->array[4]);
	printf("Taille : (%u,%u)\n",(unsigned)filesFound->real_size,(unsigned)filesFound->used_size);
	s[0]='k';
	for(int i=0; i<34; i++){
		printf(" travelling : %s",filesFound->array[i]);
	}
	free_strings(filesFound);
	free_dynamic_array(filesFound);
	return 0;
}*/

dynamic_array* new_dynamic_array(){
	dynamic_array* this=malloc(sizeof(dynamic_array));
	this->real_size=INITIAL_SIZE;
	this->used_size=0;
	this->array=malloc((this->real_size)*sizeof(string));
	
	#ifdef OOP_SWAGG
		this->free_dynamic_array=&free_dynamic_array;
		this->free_strings=&free_strings;
		this->push_back_cpy=&push_back_cpy;
		this->push_back_ptr=&push_back_ptr;
		this->at=&at;
		this->back=&back;
		this->size=&size;
	#endif
	
	return this;
}

void free_strings(dynamic_array* this){
	for(size_t i=0; i<this->used_size; i++){
		free(this->array[i]);
	}
}
void free_dynamic_array(dynamic_array* this){
	free(this->array);
	free(this);
}

void push_back_cpy(dynamic_array* this,string s){
	if(this->real_size==this->used_size){
		this->real_size=(size_t)(GROWING_RATIO*(float)this->real_size);
		this->array=realloc(this->array,sizeof(string)*this->real_size);
	}
	this->array[this->used_size]=malloc(sizeof(char)*(strlen(s)+1));
	strncpy(this->array[this->used_size],s,strlen(s)+1);
	this->used_size++;
}

void push_back_ptr(dynamic_array* this,string s){
	if(this->real_size==this->used_size){
		this->real_size=(size_t)(GROWING_RATIO*(float)this->real_size);
		this->array=realloc(this->array,sizeof(string)*this->real_size);
	}
	this->array[this->used_size]=s;
	this->used_size++;
}
string back(dynamic_array* this){
	if(this->real_size==0)return NULL;
	return this->array[this->real_size-1];
}


string at(dynamic_array* this,size_t index){
	if(index>=this->used_size)exit(1);
	return this->array[index];
}

size_t size(dynamic_array* this){
	return this->used_size;
}