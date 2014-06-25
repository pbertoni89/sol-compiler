#################################################################
#																#
#		SOL compiler makefile									#
#																#
#	This makefile allows you to compile the SOL compiler		#
#																#
#################################################################

# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@@@@@@@ MACROS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#TODO remove LEXICAL_TEST
APPLICATION ?= LEXICAL_TEST
CC:=gcc
CFLAGS:=-Wall -g
BINDIR:=bin/
SRCDIR:=src/
cyan:='\e[0;36m'
green:='\e[0;32m'
yellow:='\e[0;33m'
plain:='\e[0m'

#all the directories containing source files
VPATH := $(wildcard $(SRCDIR)*)
#output files (*.o) of the program flex (*.lex) 
FLEX_FILES := $(notdir $(patsubst %.lex, %.o, $(foreach dir, $(VPATH), $(wildcard $(dir)/*.lex))))
#output files (*.o) of the program bison (*.y) 
YACC_FILES := $(notdir $(patsubst %.y, %.o, $(foreach dir, $(VPATH), $(wildcard $(dir)/*.y))))
#output files (*.o) of the program $(CC) (aka gcc) (*.c)
CC_FILES := $(notdir $(patsubst %.c, %.o, $(foreach dir, $(VPATH), $(wildcard $(dir)/*.c))))
#all the -I directive to be passed to the $(CC) compiler
I_DIRECTIVES := $(addprefix -I ,$(VPATH))

# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@ IMPORTANT DEFINITIONS @@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#phony targets
.PHONY: all clean check-prebrequisites install uninstall \
	file-system test \
	check-prerequisites check-%

#Function to print on the stdout a target-rule successfully complete.
#param 1: the name of the rule that has been completed
#return a green message that notify the develper that the target has been completed.
target-rule-complete = @echo -e $(green)'make '$(subst target-complete-,,$(1))' correctly completed.'$(plain)

# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@@@@ MAIN RULES @@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

all: prerequisites-check optional-requisites-check file-system $(FLEX_FILES) $(YACC_FILES) $(CC_FILES) application
	$(call target-rule-complete,$@)
	

clean: 
	rm -f -r $(BINDIR)
	rm -f src/lexical/lexical.c
	rm -f src/lexical/lexical.h
	rm -f src/syntax/syntax.c
	rm -f src/syntax/syntax.h
	rm -f src/syntax/syntax.output
	$(call target-rule-complete,$@)

prerequisites-check: check-which check-flex check-$(CC) check-mkdir check-rm

optional-requisites-check: optional-check-dot optional-check-doxygen  

install:
	#TODO

uninstall:
	#TODO

# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@ SECONDARY RULES @@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


check-%:
	@echo -e $(cyan)'Checking if '$(subst check-,,$@)' command is installed on the system...'$(plain)
	@which $(subst check-,,$@) > /dev/null
	
optional-check-%:
	$(eval CMD = $(subst optional-check-,,$@))
	@echo -e $(cyan)'Checking if '$(CMD)' command is installed on the system (is optional)...'$(plain)
	@echo -ne $(if $(shell which $(CMD)),,$(yellow)'The '$(CMD)' command (optional) is not installed. The make should work however.\n'$(plain))
	$(eval unexport CMD)
	
application:
	@echo -e $(cyan)'Building the main application'$(plain)
	$(CC) $(CFLAGS) -o $(BINDIR)$(APPLICATION) $(sort $(addprefix $(BINDIR),$(FLEX_FILES)) $(addprefix $(BINDIR),$(CC_FILES)))

file-system:
	mkdir -p $(BINDIR)
	
%.o: %.c 
	$(CC) -D$(APPLICATION) -c $(CFLAGS) $(I_DIRECTIVES) -o $(BINDIR)$@ $<
	
%.o: %.lex
	$(eval BASENAME = $(basename $<))
	flex -o $(BASENAME).c --header-file=$(BASENAME).h $< 
	$(CC) -c $(CFLAGS) $(I_DIRECTIVES) $(BASENAME).c -o $(BINDIR)$@
	$(eval unexport BASENAME)

%.o: %.y
	$(eval BASENAME = $(basename $<))
	bison -v -o $(BASENAME).c --defines=$(BASENAME).h $<
	$(CC) -c $(CFLAGS) $(I_DIRECTIVES) $(BASENAME).c -o $(BINDIR)$@
	$(eval unexport BASENAME)

#TODO delete this rule at the end of the project 	
test:
	@echo "VPATH: "$(VPATH)
	@echo "CC_FILES: "$(CC_FILES)
	@echo "FLEX_FILES: "$(FLEX_FILES)
	@echo "YACC_FILES: "$(YACC_FILES)
	 
