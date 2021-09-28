CC=g++
SRC_DIR=src
FLAGS=-m64 -g3 -Wall -std=c++11
PROG_NAME=flyLog

all: main

main: Server.o TaskPool.o Task.o Worker.o StatArray.o Statistics.o RequestModule.o
	$(CC) $(FLAGS) Server.o TaskPool.o Task.o Worker.o StatArray.o Statistics.o RequestModule.o $(SRC_DIR)/main.cpp -o $(PROG_NAME) -lpthread

Server.o: $(SRC_DIR)/Server/Server.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/Server/Server.cpp

TaskPool.o:	$(SRC_DIR)/TaskPool/TaskPool.cpp
	$(CC) $(FLAGS) -c $(SRC_DIR)/TaskPool/TaskPool.cpp

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

clean:
	rm -rf *.o $(PROG_NAME)