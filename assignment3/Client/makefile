CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude -pthread

LDFLAGS:=-lboost_system -lpthread



all: StompBookClubClient

	g++ -o bin/StompBookClubClient.o bin/connectionHandler.o bin/echoClient.o bin/IOThread.o bin/ServerThread.o $(LDFLAGS) 



StompBookClubClient: bin/connectionHandler.o bin/echoClient.o bin/IOThread.o bin/ServerThread.o  

	

bin/connectionHandler.o: src/connectionHandler.cpp

	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp



bin/echoClient.o: src/echoClient.cpp

	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp



bin/ServerThread.o: src/ServerThread.cpp

	g++ $(CFLAGS) -o bin/ServerThread.o src/ServerThread.cpp



bin/IOThread.o: src/IOThread.cpp

	g++ $(CFLAGS) -o bin/IOThread.o src/IOThread.cpp

	

.PHONY: clean

clean:

	rm -f bin/*
