//
// Created by skidanov@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_IOTHREAD_H
#define BOOST_ECHO_CLIENT_IOTHREAD_H


#include <mutex>
#include <queue>
#include "connectionHandler.h"

class IOThread {

private:
    std::string frame;

    std::string decodeIOMessageToFrame(std::string& line);
    std::vector<std::string> split(std::string &line, char delim);

    ConnectionHandler& connectionHandler;
    std::string& username;

    std::map<std::string,int>& booksAndStatus;
    std::map<int,std::string>& idGenreMap;
    std::map<int,std::string>& reciptSubscriptionMap;
    std::map<std::string,std::string>& borrowMap;
    std::map<std::string,std::string>& genreBooksMap;
    std::map<int,std::string>& receiptToPrintInfoMap;
    bool connected;
    int id;
    int recipt;

    std::mutex connectionHandlerLocker;
    std::mutex booksAndStatusLocker;
    std::mutex idGenreMapLocker;
    std::mutex reciptSubscriptionMapLocker;
    std::mutex borrowMapLocker;
    std::mutex genrebooksMapLocker;
    std::mutex reciptToPrintInfoMapLocker;




public:
    std::string process(std::string response);
    void readRespones();
    void writeFrames();
    static std::string DNS(std::string ip, std::string port);
    IOThread(ConnectionHandler &connectionHandler,std::string& username,  std::map<std::string,int>& booksAndStatus, std::map<int,std::string>& idGenreMap, std::map<int,std::string>& reciptSubscriptionMap,
            std::map<std::string,std::string>& borrowMap,std::map<std::string,std::string>& genreBooksMap,std::map<int,std::string>& receiptToPrintInfoMap, bool& connected,
            std::mutex& connectionHandlerLocker,
            std::mutex& booksAndStatusLocker,
            std::mutex& idGenreMapLocker,
            std::mutex& reciptSubscriptionMapLocker,
            std::mutex& borrowMapLocker,
            std::mutex& genrebooksMapLocker,
            std::mutex& reciptToPrintInfoMapLocker) ;
    IOThread();
    void run();

};


#endif //BOOST_ECHO_CLIENT_IOTHREAD_H
