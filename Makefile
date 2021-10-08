CC=g++
SRC_DIR=src
FLAGS=-m64 -g3 -Wall -std=c++11
PROG_NAME=flyLog

all: main

main: LoggerHandler.o TaskPool.o SocketPool.o Task.o Worker.o StatArray.o Statistics.o RequestModule.o GetStatHandler.o Loader.o
	$(CC) $(FLAGS) $^ $(SRC_DIR)/main.cpp -o $(PROG_NAME) -lpthread

LoggerHandler.o: $(SRC_DIR)/Handlers/LoggerHandler.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Handlers/LoggerHandler.cpp

GetStatHandler.o: $(SRC_DIR)/Handlers/GetStatHandler.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Handlers/GetStatHandler.cpp

TaskPool.o:	$(SRC_DIR)/TaskPool/TaskPool.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/TaskPool/TaskPool.cpp

SocketPool.o:	$(SRC_DIR)/TaskPool/SocketPool.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/TaskPool/SocketPool.cpp

Task.o: $(SRC_DIR)/Task/Task.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Task/Task.cpp

Worker.o: $(SRC_DIR)/Worker/Worker.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Worker/Worker.cpp -lpthread

StatArray.o: $(SRC_DIR)/Storage/*.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Storage/*.cpp

Statistics.o: $(SRC_DIR)/Statistics/Statistics.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Statistics/Statistics.cpp

RequestModule.o: $(SRC_DIR)/Statistics/Modules/RequestModule.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Statistics/Modules/RequestModule.cpp

Loader.o: $(SRC_DIR)/Loader/Loader.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Loader/Loader.cpp

clean:
	rm -rf *.o $(PROG_NAME)