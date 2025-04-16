
LIB_DIR= ./../../../Library/Linux-x64/Debug/
INC=./../../../Include
FLAGS= -g -I$(INC) -L$(LIB_DIR) -lFlushPlatform
CPP=g++

all: Thread TestMutex
	./Thread

Thread: ./Thread.cpp
	$(CPP) ./Thread.cpp -o Thread $(FLAGS)

TestMutex: ./TestMutex.cpp
	$(CPP) ./TestMutex.cpp -o TestMutex $(FLAGS)

clear: 
	rm -rf ./Thread ./TestMutex
