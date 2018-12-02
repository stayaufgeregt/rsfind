Sources=main.c dynamic_array.c
TestSources=

Executable=rsfind
TestExecutable=test_rsfind

CFlags=-std=gnu99 -c -Wall -g -Werror -Wextra
LDFlags=-ldl

ObjectDir=obj/
SourceDir=src/
BinDir=./

TestSourceDir=test/src/
TestObjectDir=test/obj/
TestBinDir=test/

CC=gcc
RM=rm
MKDIR=mkdir -p

Objects=$(Sources:.c=.o)
TestObjects=$(TestSources:.c=.o)

CSources=$(addprefix $(SourceDir),$(Sources))
TSources=$(addprefix $(TestSourceDir),$(TestSources))

CObjects=$(addprefix $(ObjectDir),$(Objects))
TObjects=$(addprefix $(TestObjectDir),$(TestObjects))

CExecutable=$(addprefix $(BinDir),$(Executable))
TExecutable=$(addprefix $(TestBinDir),$(TestExecutable))

all: dir clean $(CSources) $(CExecutable)

clean:
	$(RM) -f $(ObjectDir)* $(BinDir)$(Executable)
	$(RM) -f $(TestObjectDir)* $(TestBinDir)$(TestExecutable)

dir:
	$(MKDIR) $(ObjectDir) $(SourceDir)
	$(MKDIR) $(TestBinDir) $(TestObjectDir) $(TestSourceDir)
	
run: $(CExecutable)
	$(CExecutable) $(ARGS)

test:  dir clean $(CSources) $(CExecutable)
	bash ./auto_test.bash

testexe: $(TExecutable)
	$(TExecutable)
	
$(CExecutable): $(CObjects)
	$(CC) $^ -o $@ $(LDFlags)

$(ObjectDir)%.o: $(SourceDir)%.c
	$(CC) $(CFlags) $^ -o $@
	
	
$(TExecutable): $(filter-out $(ObjectDir)main.o, $(CObjects)) $(TObjects)
	$(CC) $(LDFlags) $^ -o $@
	
$(TestObjectDir)%.o: $(TestSourceDir)%.c
	$(CC) $(CFlags) $^ -o $@
