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

build : $(OBJ_FILES_MAIN) $(EXECUTABLE_PATH)

$(EXECUTABLE_PATH) : $(OBJ_FILES_MAIN)
	$(CC) -o $@ $^ $(PARAMS)

.PHONY: clear

clear:
	rm -f bin/*.o
	rm -f $(EXECUTABLE_PATH)
