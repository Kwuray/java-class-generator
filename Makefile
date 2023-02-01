CC = clang++
PARAMS = -std=c++20 -Wall

EXECUTABLE_FOLDER = bin/exec
EXECUTABLE_NAME = jvcg
EXECUTABLE_PATH = $(EXECUTABLE_FOLDER)/$(EXECUTABLE_NAME)

##################################################
#Main files
MAIN_SRC_PATH = java-class/
MAIN_OBJ_PATH = bin/java-class/
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
#CLI parser files
CLI_PARSER_SRC_PATH = cli-parser/
CLI_PARSER_OBJ_PATH = bin/cli-parser/
SRC_FILES_CLI_PARSER = $(wildcard $(CLI_PARSER_SRC_PATH)*.cpp)
OBJ_FILES_CLI_PARSER = $(SRC_FILES_CLI_PARSER:$(CLI_PARSER_SRC_PATH)%.cpp=$(CLI_PARSER_OBJ_PATH)%.o)
#recipes
$(CLI_PARSER_OBJ_PATH)%.o : $(CLI_PARSER_SRC_PATH)%.cpp $(CLI_PARSER_SRC_PATH)%.h
	$(CC) -o $@ -c $< $(PARAMS)

#CLI parser files
##################################################


##################################################
#CLI RULES
CLI_RULES_SRC_PATH = cli-rules/
CLI_RULES_OBJ_PATH = bin/cli-rules/
SRC_FILES_CLI_RULES = $(wildcard $(CLI_RULES_SRC_PATH)*.cpp)
OBJ_FILES_CLI_RULES = $(SRC_FILES_CLI_RULES:$(CLI_RULES_SRC_PATH)%.cpp=$(CLI_RULES_OBJ_PATH)%.o)
#recipes
$(CLI_RULES_OBJ_PATH)%.o : $(CLI_RULES_SRC_PATH)%.cpp $(CLI_RULES_SRC_PATH)%.h
	$(CC) -o $@ -c $< $(PARAMS)

#CLI RULES
##################################################

build : $(OBJ_FILES_MAIN) $(OBJ_FILES_CLI_PARSER) $(OBJ_FILES_CLI_RULES) $(EXECUTABLE_PATH)

$(EXECUTABLE_PATH) : $(OBJ_FILES_MAIN) $(OBJ_FILES_CLI_PARSER) $(OBJ_FILES_CLI_RULES)
	$(CC) -o $@ $^ $(PARAMS)

.PHONY: clear test

clear:
	rm -f bin/*.o
	rm -f bin/cli-parser/*.o
	rm -f $(EXECUTABLE_PATH)

test:
	$(CC) -o bin/test/cli-rules.o -c cli-rules/cli-rules.cpp $(PARAMS)
	$(CC) -o bin/test/test.o -c test/test.cpp $(PARAMS)
	$(CC) -o bin/test/test bin/test/test.o bin/test/cli-rules.o $(PARAMS)
	./bin/test/test
