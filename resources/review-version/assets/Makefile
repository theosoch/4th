# Makefile variables

PROJECT_MAIN=./yforth.c
EXECUTABLE=./yforth

COMPILER=gcc
COMPILER_FLAGS=-Wall -Wextra -g -pedantic -Wformat=0
LIBRARIES_FLAGS=-lm

INCLUDE_DIRECTORY=./includes/

MODULE_DIRECTORY=./modules/
MODULES=$(wildcard $(MODULE_DIRECTORY)*.c) $(wildcard $(MODULE_DIRECTORY)*/*.c) $(wildcard $(MODULE_DIRECTORY)*/*/*.c)
# MODULES=$(shell find $(MODULE_DIRECTORY) -type f -name '*.c')

OBJECT_DIRECTORY=./objects/
OBJECTS=$(subst .c,.o,$(subst modules/,objects/,$(MODULES)))
MODULE_OBJECTS=$(MODULES:.c=.o)

PROJECT_SOURCE_DIRECTORY=./src/
PROJECT_SOURCES=$(wildcard $(PROJECT_SOURCE_DIRECTORY)*.c)
# PROJECT_SOURCES=$(shell find $(PROJECT_SOURCE_DIRECTORY) -type f -name '*.c')

# 

# Define task functions to generate some pretty task logs

define TASK_LOG
@echo "\e[38;2;128;128;128m\e[1m╠╾\e[0m ${1}\e[0m"
endef

define TASK_BEGIN
@echo ""
@echo "\e[38;2;128;128;128m\e[1m╔═\e[0m \e[38;2;255;255;255m\e[1mBegin of \e[38;2;0;255;255m\e[1m${1}\e[0m \e[38;2;255;255;255m\e[1mtask\e[0m"
@$(call TASK_LOG,\e[3mCurrent workdir : \e[0m\e[38;2;255;0;255m$(shell pwd))
endef

define TASK_END
@echo "\e[38;2;128;128;128m\e[1m╚═\e[0m \e[38;2;255;255;255m\e[1mEnd of task\e[0m"
endef

define TASK_COMMAND_EXECUTION
@$(call TASK_LOG,\e[3mExecuting : \e[0m\e[38;2;255;255;0m${1})
@$(call TASK_LOG,\e[3mLogs :)
@${1}
endef

# 

# MAKE ALL

all:
	@$(MAKE) $(EXECUTABLE) -s
	@$(MAKE) compile -s

# PROJECT COMPILATION

$(EXECUTABLE): $(OBJECTS)

compile:
	@$(call TASK_BEGIN,project compilation)

	@$(call TASK_LOG,Compiling project from \e[38;2;128;0;255m$(PROJECT_MAIN)\e[0m to \e[38;2;128;0;255m$@\e[0m)

	@$(call TASK_COMMAND_EXECUTION,$(COMPILER) $(COMPILER_FLAGS) $(PROJECT_SOURCES) $(PROJECT_MAIN) $(OBJECTS) -o $(EXECUTABLE) $(LIBRARIES_FLAGS))

	@$(call TASK_END)

# @echo //////////////// Compiling the executable \`$@\`
# @echo

# $(COMPILER) $(COMPILER_FLAGS) $(PROJECT_SOURCES) $(PROJECT_MAIN) $^ -o $@ $(LIBRARIES_FLAGS)

# @echo
# @echo /////////////////////////////////////////
# @echo

# 

# OBJECTS GENERATION

$(OBJECT_DIRECTORY)%.o: $(MODULE_DIRECTORY)%.c $(INCLUDE_DIRECTORY)%.h
	@$(call TASK_BEGIN,object generation)

	@$(call TASK_LOG,Generating object from \e[38;2;128;0;255m$<\e[0m to \e[38;2;128;0;255m$@\e[0m)

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(dir $@))
	@$(call TASK_COMMAND_EXECUTION,$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(LIBRARIES_FLAGS))

	@$(call TASK_END)

# @echo //////////////// Compiling \`$^\` to \`$@\`
# @echo

# $(COMPILER) $(COMPILER_FLAGS) -c $^ -o $@ $(LIBRARIES_FLAGS)

# @echo
# @echo //////////////////////////
# @echo

# 

# PROJECT CLEANING

clean:
	@$(call TASK_BEGIN,clean)

	@$(call TASK_COMMAND_EXECUTION,find $(OBJECT_DIRECTORY) -name '*.o' | xargs rm -f )
	@$(call TASK_COMMAND_EXECUTION,rm -f $(EXECUTABLE))

	@$(call TASK_END)

# find $(MODULE_DIRECTORY) -name '*.o' | (xargs rm -f && echo Project cleaned) || echo No file to clean

# 