#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	
	regex_t regex;
	int reti;
	char msgbuf[100];

	/* Compile regular expression */
	reti = regcomp(&regex, ".*\.c", 0);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		exit(1);
	}

	/* Execute regular expression */
	reti = regexec(&regex, "main.o", 0, NULL, 0);
	if (!reti) {
		puts("Match");
	}
	else if (reti == REG_NOMATCH) {
		puts("No match");
	}
	else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		exit(1);
	}

	/* Free memory allocated to the pattern buffer by regcomp() */
	regfree(&regex);

	return 0;
}