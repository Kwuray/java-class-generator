CC = clang++
PARAMS = -std=c++20 -Wall

EXECUTABLE_FOLDER = bin/exec
EXECUTABLE_NAME = jvcg
EXECUTABLE_PATH = $(EXECUTABLE_FOLDER)/$(EXECUTABLE_NAME)

##################################################
#Main files
MAIN_SRC_PATH = ./
MAIN_OBJ_PATH = bin/
SRC_FILES_MAIN = $(wildcard $(MAIN_SRC_PATH)*.cpp)
OBJ_FILES_MAIN = $(SRC_FILES_MAIN:$(MAIN_SRC_PATH)%.cpp=$(MAIN_OBJ_PATH)%.o)
#recipes
$(MAIN_OBJ_PATH)%.o : $(MAIN_SRC_PATH)%.cpp $(MAIN_SRC_PATH)%.h
	$(CC) -o $@ -c $< $(PARAMS)

$(MAIN_OBJ_PATH)main.o : $(MAIN_SRC_PATH)main.cpp
	$(CC) -o $@ -c $< $(PARAMS)
#Main files
##################################################

##################################################
#CLI parsef files
CLI_PARSER_SRC_PATH = ./cli-parser/
CLI_PARSER_OBJ_PATH = bin/cli-parser/
SRC_FILES_CLI_PARSER = $(wildcard $(CLI_PARSER_SRC_PATH)*.cpp)
OBJ_FILES_CLI_PARSER = $(SRC_FILES_CLI_PARSER:$(CLI_PARSER_SRC_PATH)%.cpp=$(CLI_PARSER_OBJ_PATH)%.o)
#recipes
$(CLI_PARSER_OBJ_PATH)%.o : $(CLI_PARSER_SRC_PATH)%.cpp $(CLI_PARSER_SRC_PATH)%.h
	$(CC) -o $@ -c $< $(PARAMS)

#CLI parsef files
##################################################

build : $(OBJ_FILES_MAIN) $(OBJ_FILES_CLI_PARSER) $(EXECUTABLE_PATH)

$(EXECUTABLE_PATH) : $(OBJ_FILES_MAIN) $(OBJ_FILES_CLI_PARSER)
	$(CC) -o $@ $^ $(PARAMS)

.PHONY: clear

clear:
	rm -f bin/*.o
	rm -f bin/cli-parser/*.o
	rm -f $(EXECUTABLE_PATH)
