#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <stdlib.h>
#define INITIAL_SIZE 10
#define GROWING_RATIO 1.5

//#define OOP_SWAGG

typedef char* string;

typedef struct dynarr{
	size_t real_size;
	size_t used_size;
	string* array;
	
	#ifdef OOP_SWAGG
		void (*free_dynamic_array)(struct dynarr*);
		void (*free_strings)(struct dynarr*);
		void (*push_back_cpy)(struct dynarr*,string);
		void (*push_back_ptr)(struct dynarr*,string);
		string (*at)(struct dynarr*,size_t);
		string (*back)(struct dynarr*);
		size_t (*size)(struct dynarr*);
	#endif
}dynamic_array;



dynamic_array* new_dynamic_array();
void free_dynamic_array(dynamic_array*);
void free_strings(dynamic_array*);
void push_back_cpy(dynamic_array*,string);
void push_back_ptr(dynamic_array*,string);
string at(dynamic_array*,size_t);
string back(dynamic_array*);
size_t size(dynamic_array*);

#endif