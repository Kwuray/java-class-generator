CC = clang++
PARAMS = -std=c++20 -Wall

EXECUTABLE_FOLDER = bin/exec
EXECUTABLE_NAME = jvcg
EXECUTABLE_PATH = $(EXECUTABLE_FOLDER)/$(EXECUTABLE_NAME)

##################################################
#JAVA_CLASS files
JAVA_CLASS_SRC_PATH = java-class/
JAVA_CLASS_OBJ_PATH = bin/java-class/
SRC_FILES_JAVA_CLASS = $(wildcard $(JAVA_CLASS_SRC_PATH)*.cpp)
OBJ_FILES_JAVA_CLASS = $(SRC_FILES_JAVA_CLASS:$(JAVA_CLASS_SRC_PATH)%.cpp=$(JAVA_CLASS_OBJ_PATH)%.o)
#recipes
$(JAVA_CLASS_OBJ_PATH)%.o : $(JAVA_CLASS_SRC_PATH)%.cpp $(JAVA_CLASS_SRC_PATH)%.h
	$(CC) -o $@ -c $< $(PARAMS)
#JAVA_CLASS files
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


##################################################
#MAIN FILE
SRC_FILE_MAIN = main.cpp
OBJ_FILE_MAIN = bin/main.o
#recipe
$(OBJ_FILE_MAIN) : $(SRC_FILE_MAIN)
	$(CC) -o $@ -c $< $(PARAMS)
#MAIN FILE
##################################################



build : $(OBJ_FILES_JAVA_CLASS) $(OBJ_FILES_CLI_PARSER) $(OBJ_FILES_CLI_RULES) $(EXECUTABLE_PATH) $(OBJ_FILE_MAIN)

$(EXECUTABLE_PATH) : $(OBJ_FILES_JAVA_CLASS) $(OBJ_FILES_CLI_PARSER) $(OBJ_FILES_CLI_RULES) $(OBJ_FILE_MAIN)
	$(CC) -o $@ $^ $(PARAMS)

.PHONY: clear test

clear:
	rm -f bin/*.o
	rm -f bin/test/*.o
	rm -f $(JAVA_CLASS_OBJ_PATH)/*.o
	rm -f $(CLI_PARSER_OBJ_PATH)/*.o
	rm -f $(CLI_RULES_OBJ_PATH)/*.o
	rm -f $(EXECUTABLE_PATH)

test:
	$(CC) -o bin/test/cli-rules.o -c cli-rules/cli-rules.cpp $(PARAMS)
	$(CC) -o bin/test/test.o -c test/test.cpp $(PARAMS)
	$(CC) -o bin/test/test bin/test/test.o bin/test/cli-rules.o $(PARAMS)
	./bin/test/test
