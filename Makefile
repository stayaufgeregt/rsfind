Sources=main.c rsfind.c dynamic_array.c display.c image.c cmd_exec.c cmd_parser.c opt_parser.c text_matcher.c process.c

Executable=rsfind

CFlags=-std=gnu99 -c -Wall -g -Werror -Wextra
LDFlags=-ldl -lpcre2-8 -lpthread

ObjectDir=obj/
SourceDir=src/
BinDir=./

CC=gcc
RM=rm
MKDIR=mkdir -p

Objects=$(Sources:.c=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: dir clean $(CExecutable)

clean:
	$(RM) -f $(ObjectDir)* $(BinDir)$(Executable)

dir:
	$(MKDIR) $(ObjectDir) $(SourceDir)
	
run: $(CExecutable)
	$(CExecutable) $(ARGS)

test:  dir clean $(CExecutable)
	bash ./auto_test.bash

	
$(CExecutable): $(CObjects)
	$(CC) $^ -o $@ $(LDFlags)

$(ObjectDir)%.o: $(SourceDir)%.c
	$(CC) $(CFlags) $^ -o $@
