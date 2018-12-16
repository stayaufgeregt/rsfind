#define PCRE2_CODE_UNIT_WIDTH 8


#include <pcre2.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char** argv){

	// bool hasT(char* name)

	PCRE2_SPTR strCompare =(PCRE2_SPTR) "the cat sat on the mat"; // remplacer char* name par myArgs.T
	PCRE2_SPTR pattern =(PCRE2_SPTR) "cat"; // remplacer "/nd/" par myArgs.T


	pcre2_code* regexPattern;
	pcre2_match_data *match_data;
	int errornumber;
	PCRE2_SIZE erroroffset;

	regexPattern = pcre2_compile(pattern,PCRE2_ZERO_TERMINATED,0,&errornumber,&erroroffset,NULL);
	if (regexPattern == NULL)
  {
  PCRE2_UCHAR buffer[256];
  pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
  printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset,
    buffer);
  return 1;
  }

	match_data = pcre2_match_data_create_from_pattern(regexPattern, NULL);
	printf("%s\n",(char*)match_data);

	int a = pcre2_match(regexPattern,strCompare,strlen((char *)strCompare),0,0,match_data,NULL);
	
if (a < 0)
  {
  switch(a)
    {
    case PCRE2_ERROR_NOMATCH: printf("No match\n"); break;
    /*
    Handle other special cases if you like
    */
    default: printf("Matching error %d\n", a); break;
    }
  pcre2_match_data_free(match_data);   /* Release memory used for the match */
  pcre2_code_free(regexPattern);                 /* data and the compiled pattern. */
  return 1;
  }

	if(a){
		printf("%d\n",a);
	}
}
    