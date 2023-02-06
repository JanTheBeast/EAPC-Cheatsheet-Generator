PROJECT_NAME = sheet

CC = g++

CPPFLAGS = -O3 -g -Wall -Wextra -Werror -Wpedantic -Wstrict-aliasing -static -static-libgcc -static-libstdc++
#CPPFLAGS += -Iinclude

LDFLAGS += -lshlwapi #-mwindows

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: project

run: all
	$(BIN)/$(PROJECT_NAME)

project: $(OBJ)
	$(CC) -o $(BIN)/$(PROJECT_NAME) $^ $(LDFLAGS)

clean:
	del /S "src\*.o"
