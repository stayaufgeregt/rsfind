#ifndef TEXT_MATCHER_H_
#define TEXT_MATCHER_H_

#define PCRE2_CODE_UNIT_WIDTH 8
#include <sys/stat.h>
#include <stdbool.h>

///true if the needle is in the haystack
bool regexPerl(char* haystack,char* needle);
///true if the name matches the glob pattern passed to --ename
bool regexNameMatch(char* name);
///true if the files's text contains the regex passed to -T
bool regexTextMatch(char* path,struct stat* path_stat);
///true if name equals the string passed to --name
bool hasName(char* name);
///true if the file's text contains the string passed to -t
bool hasText(char* path,struct stat* path_stat);

#endif