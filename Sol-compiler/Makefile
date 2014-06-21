#################################################################
#																#
#		SOL compiler makefile									#
#																#
#	This makefile allows you to compile the SOL compiler		#
#																#
#################################################################


CC:=gcc
CFLAGS:=-Wall -g
BINDIR:=bin/
SRCDIR:=src/

VPATH = $(wildcard $(SRCDIR)*)
#output files of the program flex 
FLEX_FILES = $(notdir $(patsubst %.lex, %.c, $(foreach dir, $(VPATH), $(wildcard $(dir)/*.lex))))
#output files of the program $(CC) (aka gcc)
CC_FILES = $(notdir $(patsubst %.c, %.o, $(foreach dir, $(VPATH), $(wildcard $(dir)/*.c)))) $(addsuffix .o, $(basename $(FLEX_FILES)))


.PHONY: all clean file-system check 

all: file-system $(CC_FILES)

clean:
	rm -f -r $(BINDIR)
	rm -f src/lexical/lexical.c

check-prerequisites:
	#TODO check if flex and bison are installed...

test:
	@echo "VPATH: "$(VPATH)
	@echo "CC_FILES: "$(CC_FILES)
	@echo "FLEX_FILES":$(FLEX_FILES)
	@echo $(basename $(FLEX_FILES))

file-system:
	mkdir -p $(BINDIR)
	
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(BINDIR)$@
	 
%.o: %.lex
	flex -o $(basename $<).c $<
	$(CC) -c $(CFLAGS) $(addprefix -I ,$(VPATH)) $(basename $<).c -o $(BINDIR)$@
	 
