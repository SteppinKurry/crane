#OBJS specifies which files to compile as part of the project
OBJS = crane.c $(CURDIR)/src/*.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -I$(CURDIR)/src/ -I$(CURDIR)/include/ -L$(CURDIR)/lib/

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lm

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = crane

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)
