//
// Created by skidanov@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include <thread>
#include "IOThread.h"

#define LOGIN "login"
#define JOIN "join"
#define EXIT "exit"
#define ADD "add"
#define BORROW "borrow"
#define RETURN "return"
#define STATUS "status"
#define LOGOUT "logout"

#define SEND_FRAME          "SEND"
#define CONNENCT_FRAME      "CONNECT"
#define DISCONNECT_FRAME    "DISCONNECT"
#define SUBSCRIBE_FRAME     "SUBSCRIBE"
#define UNSUBSCRIBE_FRAME   "UNSUBSCRIBE"
#define DESTINATION         "destination"

#define OWN_BOOK 1
#define WISH_BOOK 5

/*
 * Constructor
 */
IOThread::IOThread(ConnectionHandler &connectionHandler, std::string &username,std::map<std::string, int> &booksAndStatus, std::map<int, std::string> &idGenreMap,
                   std::map<int, std::string> &reciptSubscriptionMap, std::map<std::string, std::string> &borrowMap,std::map<std::string,std::string> &genreBooksMap,std::map<int,std::string>& receiptToPrintInfoMap, bool& connected,
                   std::mutex& connectionHandlerLocker,
                   std::mutex& booksAndStatusLocker,
                   std::mutex& idGenreMapLocker,
                   std::mutex& reciptSubscriptionMapLocker,
                   std::mutex& borrowMapLocker,
                   std::mutex& genrebooksMapLocker,
                   std::mutex& reciptToPrintInfoMapLocker):
                   frame(""),connectionHandler(connectionHandler), username(username), booksAndStatus(booksAndStatus), idGenreMap(idGenreMap), reciptSubscriptionMap(reciptSubscriptionMap),
                   borrowMap(borrowMap),genreBooksMap(genreBooksMap), receiptToPrintInfoMap(receiptToPrintInfoMap),connected(connected), id(0), recipt(1),
                   connectionHandlerLocker(), booksAndStatusLocker(), idGenreMapLocker(), reciptSubscriptionMapLocker(), borrowMapLocker(), genrebooksMapLocker(), reciptToPrintInfoMapLocker()
{}


void IOThread::run() {

    while (connectionHandler.getIsConnected()) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        if ((split(line, ' ')[0] == LOGIN) || (split(line, ' ')[0] == LOGOUT)) {
            line = decodeIOMessageToFrame(line);
            connectionHandlerLocker.lock();
            if (!connectionHandler.sendLine(line)) {
                std::cout << "Disconnected from send line. Exiting...\n" << std::endl;
                break;
            }
            connectionHandlerLocker.unlock();
            break;
        }
        line = decodeIOMessageToFrame(line);

        if (connectionHandler.getIsConnected() && !line.empty()) {
            connectionHandlerLocker.lock();
            if (!connectionHandler.sendLine(line)) {
                std::cout << "Disconnected from send line. Exiting...\n" << std::endl;
                break;
            }
            connectionHandlerLocker.unlock();
        }
    }
}

/*
 * This function receives a string from the IO as a message and converts it into a frame and returns it
 * @param std::string& is the line to convert to frame
 * @return std::string frame
 */
std::string IOThread::decodeIOMessageToFrame(std::string& line) {
    std::vector<std::string> tokens;
    tokens = split(line, ' ');
    std::string book = "";
    bool firstElement = true;
    if(tokens[0] == ADD || tokens[0] == BORROW || tokens[0] == RETURN) {
        for(int i=2;i<(signed)tokens.size();i++) {
            if(firstElement == true)
            {
                book.append(tokens[i]);
                firstElement = false;
            }
            else {
                book.append(" " + tokens[i]);
            }
        }
    }
    std::string frame;

    if (tokens[0] == JOIN) {

        frame.append("SUBSCRIBE\ndestination:" + tokens[1] + "\nid:" + std::to_string(id) +  "\nreceipt:" + std::to_string(recipt)+"\n\n");

        idGenreMapLocker.lock();
        idGenreMap.insert(std::pair<int,std::string>(id++, tokens[1]));
        idGenreMapLocker.unlock();

        reciptSubscriptionMap.insert(std::pair<int,std::string>(recipt,tokens[0]));
        std::string printInfo = "Joined club {" + tokens[1] + "}";
        receiptToPrintInfoMap.insert(std::pair<int,std::string>(recipt++,printInfo));

    }
    else if (tokens[0] == ADD) {

        frame.append("SEND\ndestination:" + tokens[1] + "\n\n" + this->username + " has added the book " + book + "\n");

        booksAndStatusLocker.lock();
        this->booksAndStatus.insert(std::pair<std::string,int>(book,OWN_BOOK));
        booksAndStatusLocker.unlock();

        genrebooksMapLocker.lock();
        this->genreBooksMap.insert(std::pair<std::string,std::string>(book,tokens[1]));
        genrebooksMapLocker.unlock();

    }

    else if (tokens[0] == EXIT) {

        frame.append("UNSUBSCRIBE\ndestination:" + tokens[1] + "\nid:" + std::to_string(id) +  "\nreceipt:" + std::to_string(recipt)+"\n");

        idGenreMapLocker.lock();
        for(std::pair<int,std::string> pair : idGenreMap) {
            if(pair.second == tokens[1]) {
                idGenreMap.erase(pair.first);
                break;
            }
        }
        idGenreMapLocker.unlock();

        reciptSubscriptionMapLocker.lock();
        reciptSubscriptionMap.insert(std::pair<int,std::string>(recipt,tokens[0]));
        reciptSubscriptionMapLocker.unlock();

        reciptToPrintInfoMapLocker.lock();
        receiptToPrintInfoMap.insert(std::pair<int,std::string>(recipt++,"Exited club {" + tokens[1] + "}"));
        reciptToPrintInfoMapLocker.unlock();

    }
    else if (tokens[0] == BORROW) {

        frame.append("SEND\ndestination:" + tokens[1] + "\n\n" + this->username + " wish to borrow " + book + "\n");

    }
    else if (tokens[0] == RETURN) {
        if(borrowMap.find(book) != borrowMap.end()) {
            frame.append("SEND\ndestination:" + tokens[1] + "\n\n" + "Returning " + book + " to " + borrowMap.at(book) +
                         "\n");
        }

    }
    else if (tokens[0] == STATUS) {

        frame.append("SEND\ndestination:" + tokens[1] + "\n\nBook status\n");

    }
    else if(tokens[0] == LOGOUT) {

        frame.append("DISCONNECT\nreceipt:" + std::to_string(recipt)+"\n");

        reciptSubscriptionMapLocker.lock();
        reciptSubscriptionMap.insert(std::pair<int,std::string>(recipt++,tokens[0]));
        reciptSubscriptionMapLocker.unlock();
    }

    /*std::cout << "====================== FRAME ====================" << std::endl;
    std::cout << frame << std::endl;
    std::cout << "=================================================\n" << std::endl;
     */
    return frame;
}

/*
 * This function splits a string to a vector of tokens, using a given delimiter for splitting
 * @param std::string &line is a reference to the string to split
 * @param char delim is the delimeter for splitting the string
 * @return vector<std::string> a vector of tokens
 */
std::vector<std::string> IOThread::split(std::string &line, char delim) {
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



