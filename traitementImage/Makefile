##### General rules
	## Compiler options
	CC = clang++
	# CC = g++		
	CFLAGS = #-Wall
	TARGET = testTraitementImage

	## Sources
	SRC += main.cpp
	SRC += fonction_traitementImage.cpp

	## Objects
	OBJ=$(SRC:.cpp=.o)

	## Headers
	INC += main.hpp
	INC += fonction_traitementImage.hpp

	## For OpencCV lib
	INC_PATH +=
	LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml
	LIBS += -lopencv_video -lopencv_features2d
	LIBS += -lopencv_calib3d -lopencv_objdetect -lopencv_legacy -lopencv_flann

##### Rules
### Default
default: all
.PHONY: default

all: $(TARGET)
.PHONY: all

### DEBUG
debug: CFLAGS += -DDEBUG
debug: all
.PHONY: debug

### Sans l'erreur Unused
nounused: CFLAGS += -Wno-unused
nounused: all
.PHONY: nounused

#### Pour travailler en connexion avec la camera robotino
robotino: LIBS += -lrec_robotino_com -lrec_core_lt
robotino: INC_PATH += -I$(OPENROBOTINOAPI_DIR)/1/include -I$(OPENROBOTINOAPI_DIR)/share/include
robotino: LIB_PATH += -L$(OPENROBOTINOAPI_DIR)/1/lib/linux
robotino: SRC += robotino.cpp
robotino: SRC += CameraView.cpp
robotino: INC += CameraView.hpp
robotino: all
.PHONY: robotino
	
### Link executable
$(TARGET): obj
	$(CC) $(LIB_PATH) -o $(TARGET) $(OBJ) $(LIBS)
	
### Compile objetcs files
obj: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(INC_PATH) -c $(SRC)

### Clean
#### Retire les fichiers inutiles
clean: 
	rm -f $(OBJ)
	rm -f *~
#### Retire les fichiers inutiles et l'executable
mrproper: clean
	rm -f $(TARGET)

.PHONY: clean mrproper