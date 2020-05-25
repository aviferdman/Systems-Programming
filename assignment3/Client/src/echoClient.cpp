//
// Created by skidanov@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <stdlib.h>
#include <connectionHandler.h>
#include "ServerThread.h"
#include "IOThread.h"
#include <queue>
#include <thread>


std::vector<std::string> split(std::string &line, char delim) {
    std::vector<std::string> tokens;
    char delimiter = delim;
    std::string token;
    std::string emptyString = "";

    for(unsigned int i=0;i<line.length();i++)
    {
        if(line.at(i) != delimiter)
        {
            token += line[i];
        }
        else
        {
            tokens.push_back(token);
            token.clear();
        }
    }

    if(token != emptyString){
        tokens.push_back(token);
    }

    return tokens;
}


int main (int argc, char *argv[]) {


    std::string* username = new std::string();
    std::map<std::string,int>* booksAndStatus = new std::map<std::string,int>();
    std::map<int,std::string>* idGenreMap = new std::map<int,std::string>();
    std::map<int,std::string>* reciptSubscriptionMap = new std::map<int,std::string>();
    std::map<std::string,std::string>* booksOwnerMap = new std::map<std::string,std::string>();
    std::map<std::string,std::string>* genreBooksMap = new std::map<std::string,std::string>();
    std::map<int,std::string>* receiptToPrintInfoMap = new std::map<int,std::string>();

    std::mutex* connectionHandlerLocker = new std::mutex();
    std::mutex* booksAndStatusLocker = new std::mutex();
    std::mutex* idGenreMapLocker = new std::mutex();
    std::mutex* reciptSubscriptionMapLocker = new std::mutex();
    std::mutex* borrowMapLocker = new std::mutex();
    std::mutex* genrebooksMapLocker = new std::mutex();
    std::mutex* reciptToPrintInfoMapLocker = new std::mutex();



    bool* connected = new bool();
    *connected = true;
    ConnectionHandler* connectionHandler;
    bool isLegal = false;

    bool tryConnect = true;
    while(tryConnect) {
        //std::cout << "Insert login" << std::endl;
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        std::vector<std::string> tokens;
        tokens = split(line, ' ');

        if( tokens.size() == 4 && tokens[0] == "login" && tokens[1].find(":")!= std::string::npos)
        {
            std::string hostStr = split(tokens[1],':')[0];
            std::string portStr = split(tokens[1],':')[1];
            const char* p = portStr.c_str();
            short port = std::atoi(p);
            connectionHandler = new ConnectionHandler(hostStr, port);
            try {
                connectionHandler->connect();
            }
            catch (std::exception){
                std::cout << "could'nt connect" << std::endl;
            }
            *username = tokens[2];
            std::string frame =("CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + tokens[2] + "\npasscode:" + tokens[3] + "\n\n\0");
            (*reciptSubscriptionMap).insert(std::pair<int,std::string>(0,tokens[0]));
            (*receiptToPrintInfoMap).insert(std::pair<int,std::string>(0,"Login Successful!"));
                try {
                    connectionHandler->sendLine(frame);
                }
                catch (std::exception){
                    std::cout << "could'nt send" << std::endl;
                }
            //need to add here if this is not an error!
            std::string answer;
            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
            try {
                if (!connectionHandler->getLine(answer)) {
                    std::cout << "Disconnected from get line. Exiting...\n" << std::endl;
                }
            }
            catch (std::exception){

            }
            std::cout << answer << std::endl;
            if(((*reciptSubscriptionMap).at(0) == "login")) {
                std::cout << (*receiptToPrintInfoMap).at(0) << std::endl;
            }
            if (!answer.find("ERROR")) {
                //shut him out!
                break;
            } else{
                isLegal = true;
                break;
            }
        }
    }

    if(isLegal) {
        ServerThread *serverThread = new ServerThread(*connectionHandler, *username, *booksAndStatus, *idGenreMap,*reciptSubscriptionMap, *booksOwnerMap, *genreBooksMap,*receiptToPrintInfoMap,*connected,
        *connectionHandlerLocker, *booksAndStatusLocker, *idGenreMapLocker, *reciptSubscriptionMapLocker, *borrowMapLocker, *genrebooksMapLocker, *reciptToPrintInfoMapLocker);
        IOThread *ioThread = new IOThread(*connectionHandler, *username, *booksAndStatus, *idGenreMap,
                                          *reciptSubscriptionMap, *booksOwnerMap, *genreBooksMap,*receiptToPrintInfoMap, *connected,        *connectionHandlerLocker, *booksAndStatusLocker, *idGenreMapLocker, *reciptSubscriptionMapLocker, *borrowMapLocker, *genrebooksMapLocker, *reciptToPrintInfoMapLocker);
        std::thread io(&IOThread::run, ioThread);
        std::thread server(&ServerThread::run, serverThread);
        io.join();
        server.join();
        delete(serverThread);
        delete(ioThread);
    }

    //TODO delete the pointers!
    delete(booksAndStatus);
    delete(idGenreMap);
    delete(reciptSubscriptionMap);
    delete(booksOwnerMap);
    delete(genreBooksMap);
    delete(receiptToPrintInfoMap);
    delete(connectionHandler);
    delete(connected);
    delete(username);
    delete(connectionHandlerLocker);
    delete(booksAndStatusLocker);
    delete(idGenreMapLocker);
    delete(reciptSubscriptionMapLocker);
    delete(borrowMapLocker);
    delete(genrebooksMapLocker);
    delete(reciptToPrintInfoMapLocker);



}







