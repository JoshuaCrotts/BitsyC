#OBJS specifies which files to compile as part of the project
OBJS = src/*.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresszzes all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Werror -Wfloat-conversion -ggdb -g 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bitsyc

#This is the target that compiles our executable
#
# -g -O -c generates .o files.
# -shared -o
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)