MODULE = sudoku

sudoku = sudoku
sudoku2 = sudoku2

TARGET_DIR = ./bins
TARGET = $(TARGET_DIR)

#get all files from include folder
INC_PATH = -I ./inc \

#get all files from source folder 
INC_SRC = $(wildcard ./src/*.cc) \
		  $(wildcard ../config/src/*.cc) 

#compiler type
compiler = g++
#C++ standard
STD = -std=c++14
#compiler flags
CFLAGS = $(compiler) -g $(STD) #-Wall -Werror
#linker flags
LFLAGS = -pthread#-lgtest -lgtest_main -lgmock -lgmock_main -pthread -ljsoncpp -lprotobuf

all: $(TARGET)

$(TARGET):
	@echo $(INC_SRC)
	@echo $(INC_HD)
	mkdir -pv $(TARGET)
	$(CFLAGS) ./$(sudoku).cpp $(INC_SRC) $(INC_PATH) -o $@/$(sudoku).out $(LFLAGS)

clean:
	rm -rf $(TARGET_DIR)

.PHONY: clean all