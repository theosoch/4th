# Makefile variables

DISTRIBUTION_DIRECTORY=./dist/

EXECUTABLE=$(DISTRIBUTION_DIRECTORY)4th

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

PROJECT_MAIN_FILENAME=main.c

REVIEW_VERSION_DIRECTORY=./review-version/
REVIEW_VERSION_ASSETS_DIRECTORY=./resources/review-version/assets/
REVIEW_VERSION_MAIN_FILENAME=yforth.c
REVIEW_VERSION_ARCHIVE=$(DISTRIBUTION_DIRECTORY)review-version.zip
REVIEW_VERSION_NAME_FILENAME=review-version.name

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

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(DISTRIBUTION_DIRECTORY))

	@$(call TASK_LOG,Compiling project from \e[38;2;128;0;255m$(PROJECT_MAIN)\e[0m to \e[38;2;128;0;255m$@\e[0m)

	@$(call TASK_COMMAND_EXECUTION,$(COMPILER) $(COMPILER_FLAGS) $(PROJECT_SOURCES) $(OBJECTS) -o $(EXECUTABLE) $(LIBRARIES_FLAGS))

	@$(call TASK_END)

# 

# OBJECTS GENERATION

$(OBJECT_DIRECTORY)%.o: $(MODULE_DIRECTORY)%.c $(INCLUDE_DIRECTORY)%.h
	@$(call TASK_BEGIN,object generation)

	@$(call TASK_LOG,Generating object from \e[38;2;128;0;255m$<\e[0m to \e[38;2;128;0;255m$@\e[0m)

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(dir $@))
	@$(call TASK_COMMAND_EXECUTION,$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(LIBRARIES_FLAGS))

	@$(call TASK_END)
	
# 

# PROJECT CLEANING

clean:
ifneq (rv-make,$(firstword $(MAKECMDGOALS)))
	@$(call TASK_BEGIN,clean)
	
	@$(call TASK_COMMAND_EXECUTION,find $(OBJECT_DIRECTORY) -name '*.o' | xargs rm -f )

	@$(call TASK_END)
endif

# 

# ///////// ///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////

# GENERATING THE PROJECT REVIEW VERSION

rv-gen: rv-clean
	@$(call TASK_BEGIN,rv-gen)

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(REVIEW_VERSION_DIRECTORY))

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(REVIEW_VERSION_DIRECTORY)includes)
	@$(call TASK_COMMAND_EXECUTION,cp -r $(INCLUDE_DIRECTORY)* $(REVIEW_VERSION_DIRECTORY)includes/ || echo No source to copy)
	
	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(REVIEW_VERSION_DIRECTORY)modules)
	@$(call TASK_COMMAND_EXECUTION,cp -r $(MODULE_DIRECTORY)* $(REVIEW_VERSION_DIRECTORY)modules/ || echo No module to copy)
	@$(call TASK_COMMAND_EXECUTION,find $(REVIEW_VERSION_DIRECTORY)modules -name '*.o' | xargs rm -f )
	
	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(REVIEW_VERSION_DIRECTORY)src)
	@$(call TASK_COMMAND_EXECUTION,cp -r $(PROJECT_SOURCE_DIRECTORY)* $(REVIEW_VERSION_DIRECTORY)src/ || echo No source to copy)

	@$(call TASK_COMMAND_EXECUTION,mv $(REVIEW_VERSION_DIRECTORY)src/$(PROJECT_MAIN_FILENAME) $(REVIEW_VERSION_DIRECTORY)$(REVIEW_VERSION_MAIN_FILENAME))

	@$(call TASK_COMMAND_EXECUTION,sed -i 's/..\/includes/.\/includes/' $(REVIEW_VERSION_DIRECTORY)$(REVIEW_VERSION_MAIN_FILENAME))
	@$(call TASK_COMMAND_EXECUTION,sed -i 's/REVIEW_VERSION 0/REVIEW_VERSION 1/' $(REVIEW_VERSION_DIRECTORY)$(REVIEW_VERSION_MAIN_FILENAME))

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(REVIEW_VERSION_ASSETS_DIRECTORY))
	@$(call TASK_COMMAND_EXECUTION,cp -r $(REVIEW_VERSION_ASSETS_DIRECTORY)/* $(REVIEW_VERSION_DIRECTORY) || echo No asset to copy)

	@$(call TASK_COMMAND_EXECUTION,find $(REVIEW_VERSION_DIRECTORY) -type d -empty | xargs rm -d || printf '')

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(DISTRIBUTION_DIRECTORY))

ifneq (,$(shell cat $(REVIEW_VERSION_NAME_FILENAME) || printf ''))
	@$(call TASK_COMMAND_EXECUTION,\
		export review_version_name=$(shell cat $(REVIEW_VERSION_NAME_FILENAME))\
		&& mv $(REVIEW_VERSION_DIRECTORY) $$review_version_name\
		&& zip -q -r $(DISTRIBUTION_DIRECTORY)$$review_version_name.zip $$review_version_name\
		&& mv $$review_version_name $(REVIEW_VERSION_DIRECTORY)\
	)
else
	@$(call TASK_COMMAND_EXECUTION,\
		printf 'Please enter the name of the review version : '\
		&& read review_version_name\
		&& echo Review version name stored in \'$(REVIEW_VERSION_NAME_FILENAME)\' to be reused in the future.\
		&& mv $(REVIEW_VERSION_DIRECTORY) $$review_version_name\
		&& zip -q -r $(DISTRIBUTION_DIRECTORY)$$review_version_name.zip $$review_version_name\
		&& mv $$review_version_name $(REVIEW_VERSION_DIRECTORY)\
		&& printf $$review_version_name >$(REVIEW_VERSION_NAME_FILENAME)\
	)
endif

	@$(call TASK_END)

# 

# CLEANING THE PROJECT REVIEW VERSION

rv-clean:
	@$(call TASK_BEGIN,rv-clean)

	@$(call TASK_COMMAND_EXECUTION,find $(REVIEW_VERSION_DIRECTORY) -name '*.*' | xargs rm -f )
	@$(call TASK_COMMAND_EXECUTION,rm -rf $(REVIEW_VERSION_DIRECTORY)*)
	@$(call TASK_COMMAND_EXECUTION,rm -rf -d $(REVIEW_VERSION_DIRECTORY)*)

	@$(call TASK_END)

#

# BUILD REVIEW VERSION

rv-make:
	@$(call TASK_BEGIN,rv-build)

	@$(call TASK_COMMAND_EXECUTION,cd $(REVIEW_VERSION_DIRECTORY) && make $(filter-out $(firstword $(MAKECMDGOALS)),$(MAKECMDGOALS)) && cd ..)
	@echo

	@$(call TASK_END)

# 