OPENROBOTINOAPI_DIR = /usr/local/OpenRobotinoAPI

LIBPATH = $(OPENROBOTINOAPI_DIR)/1/lib/linux
LIBPATH2 = $(OPENROBOTINOAPI_DIR)/share/lib/linux
INCPATH = $(OPENROBOTINOAPI_DIR)/1/include -I$(OPENROBOTINOAPI_DIR)/external/include
INCPATH2 = $(OPENROBOTINOAPI_DIR)/share/include
INCPATH3 = $(OPENROBOTINOAPI_DIR)/external/include

CFLAGS = -Dlinux32 -Wall -I$(INCPATH) -I$(INCPATH2) -I$(INCPATH3) 
LDFLAGS = -Wl,-rpath,$(LIBPATH),-rpath,$(LIBPATH2) -L$(LIBPATH) -L$(LIBPATH2) -lrec_robotino_com -lrec_core_lt
CC = g++
OBJ = main.o

TARGET = basic_move

all: $(TARGET)

test:
	@echo 'Test var'
	@echo $(value OPENROBOTINOAPI_DIR)

clean:
	rm -f *.o $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $? -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $? -o $@
