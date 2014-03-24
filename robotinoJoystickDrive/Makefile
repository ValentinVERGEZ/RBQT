CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lrec_robotino_com -lrec_core_lt
INC_PATH = -I$(OPENROBOTINOAPI_DIR)/1/include -I$(OPENROBOTINOAPI_DIR)/share/include
LIB_PATH = -L$(OPENROBOTINOAPI_DIR)/1/lib/linux
CFLAGS = -Wall
TARGET = driveRobotino
SRC=main.cpp robotino_drive.cpp
OBJ=$(SRC:.cpp=.o)
INC=main.hpp robotino_drive.hpp



####
default: all
.PHONY: default

all: $(TARGET)
.PHONY: all

$(TARGET): obj
	$(CC) $(LIB_PATH) -o $(TARGET) $(OBJ) $(LIBS)

obj: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(INC_PATH) -c $(SRC)

clean: 
	rm $(OBJ)
.PHONY: clean

mrproper: clean
	rm $(TARGET)
.PHONY: mrproper