Sources=main.c dynamic_array.c image.c cmd_parser.c opt_parser.c text_matcher.c

Executable=rsfind

CFlags=-std=gnu99 -c -Wall -g -Werror -Wextra
LDFlags=-ldl -lpcre2-8

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

test:  dir clean $(CSources) $(CExecutable)
	bash ./auto_test.bash

	
$(CExecutable): $(CObjects)
	$(CC) $^ -o $@ $(LDFlags)

$(ObjectDir)%.o: $(SourceDir)%.c
	$(CC) $(CFlags) $^ -o $@
