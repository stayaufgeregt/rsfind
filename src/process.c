#include "process.h"
#include "display.h"
#include "cmd_exec.h"
#include "structures.h"


void applyAction(char* path){
	if(!myArgs.flags[_p]){
		if( myArgs.flags[_print] || (!myArgs.flags[_exec] && !myArgs.flags[_l]) ){
			simpleDisplay(path);
		}
		
		if(myArgs.flags[_l]){
			detailedDisplay(path);
		}
		
		if(myArgs.flags[_exec]){
			execCmdOn(path);
		}
	}
	else{
		if( myArgs.flags[_print] || (!myArgs.flags[_exec] && !myArgs.flags[_l]) ){
			simpleDisplay(path);
		}
		
		if(myArgs.flags[_l]){
			detailedDisplay(path);
		}
		
		if(myArgs.flags[_exec]){
			execCmdOn(path);
		}
		
	}
}


void* applyAction_thread(char* path){
	
	path=path;
	return NULL;
}