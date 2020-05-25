//
// Created by skidanov@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERTHREAD_H
#define BOOST_ECHO_CLIENT_SERVERTHREAD_H

#include <queue>
#include <mutex>
#include "connectionHandler.h"

class ServerThread{
public:
    ServerThread(ConnectionHandler &connectionHandler,std::string& username,  std::map<std::string,int>& booksAndStatus, std::map<int,std::string>& idGenreMap, std::map<int,std::string>& reciptSubscriptionMap,
                 std::map<std::string,std::string>& borrowMap,std::map<std::string,std::string>& genreBooksMap,std::map<int,std::string>& receiptToPrintInfoMap, bool& connected,
                 std::mutex& connectionHandlerLocker,
                 std::mutex& booksAndStatusLocker,
                 std::mutex& idGenreMapLocker,
                 std::mutex& reciptSubscriptionMapLocker,
                 std::mutex& borrowMapLocker,
                 std::mutex& genrebooksMapLocker,
                 std::mutex& reciptToPrintInfoMapLocker) ;
    void run();
    void decodeFrame(std::string line);
    std::vector<std::string> split(std::string &line, char delim);
    std::string parseBookName(std::string body);
    int calculateBookLength(std::string bookName);

private:
    ConnectionHandler& connectionHandler;
    std::string& username;

    std::map<std::string,int>& booksAndStatus;
    std::map<int,std::string>& idGenreMap;
    std::map<int,std::string>& reciptSubscriptionMap;
    std::map<std::string,std::string>& borrowMap;
    std::map<std::string,std::string>& genreBooksMap;
    std::map<int,std::string>& receiptToPrintInfoMap;

    std::string responseFrame;
    bool connected;


    std::mutex connectionHandlerLocker;
    std::mutex booksAndStatusLocker;
    std::mutex idGenreMapLocker;
    std::mutex reciptSubscriptionMapLocker;
    std::mutex borrowMapLocker;
    std::mutex genrebooksMapLocker;
    std::mutex reciptToPrintInfoMapLocker;


};

#endif //BOOST_ECHO_CLIENT_SERVERTHREAD_H
