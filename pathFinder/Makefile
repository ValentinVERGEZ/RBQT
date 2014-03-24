CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -Wall -Wextra
DEFINES = 
TARGET = pathFinder
SRC=main.cpp Map.cpp Objet.cpp Point.cpp
OBJ=$(SRC:.cpp=.o)
INC=main.hpp Map.hpp Objet.hpp Point.hpp



####
default: all
.PHONY: default

all: $(TARGET)
.PHONY: all

graphic: CFLAGS += -DGRAPHIC
graphic: all
.PHONY: graphic

$(TARGET): obj
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

obj: $(SRC) $(INC)
	$(CC) $(CFLAGS) -c $(SRC)

clean: 
	rm $(OBJ)
.PHONY: clean

mrproper: clean
	rm $(TARGET)
.PHONY: mrproper