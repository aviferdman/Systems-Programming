//
// Created by skidanov@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include <ServerThread.h>
#include <thread>

#define CONNECTED_FRAME "CONNECTED"
#define MESSAGE_FRAME   "MESSAGE"
#define ERROR_FRAME     "ERROR"
#define RECEIPT_FRAME   "RECEIPT"


#define OWN_BOOK 1
#define WAITING_FOR_BOOK 3
#define WISH_BOOK 5

void ServerThread::run () {
    std::vector<std::string> tokens;

    while (connected) {

        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;

        connectionHandlerLocker.lock();
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected from get line. Exiting...\n" << std::endl;
            break;
        }
        connectionHandlerLocker.unlock();

        /*std::cout << "------------------ Start Reply ------------------" << std::endl;
        std::cout << answer << std::endl;
        std::cout << "------------------- End Reply -------------------\n\n" << std::endl;
         */

        std::cout << answer << std::endl;

        decodeFrame(answer);

        /*if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }*/
    }
}

void ServerThread::decodeFrame(std::string line) {
    std::vector<std::string> tokens = split(line, '\n');
    responseFrame.clear();
    try {
        if (tokens[0] == CONNECTED_FRAME) {

        } else if (tokens[0] == MESSAGE_FRAME) {
            if (tokens[5].find(":") != std::string::npos) {
                return;
            }
            std::string book = parseBookName(tokens[5]);
            std::vector<std::string> bodyTokens = split(tokens[5], ' ');
            std::string genre = split(tokens[3], ':')[1];
            if (bodyTokens[1] == "has" && bodyTokens[2] == "added") {
                //booksAndStatus.insert(std::pair<std::string, int>(bodyTokens[5], 1));
                //std::cout << tokens[5] << std::endl;
            } else if (bodyTokens[1] == "wish") {
                if(username == bodyTokens[0]) {

                    booksAndStatusLocker.lock();
                    booksAndStatus.insert(std::pair<std::string, int>(book, WISH_BOOK));
                    booksAndStatusLocker.unlock();
                }
                if (booksAndStatus.find(book) != booksAndStatus.end() && booksAndStatus.at(book) == OWN_BOOK) {

                    responseFrame.append("SEND\ndestination:" + genre + "\n\n" + username + " has " + book + "\n");

                    connectionHandlerLocker.lock();
                    connectionHandler.sendLine(responseFrame);
                    connectionHandlerLocker.unlock();
                }
            } else if (bodyTokens[1] == "has" && bodyTokens[2]!= "added") { // "john has dune"
                if(booksAndStatus.find(book) != booksAndStatus.end() && booksAndStatus.at(book) == WISH_BOOK) {

                    responseFrame.append("SEND\ndestination:" + genre + "\n\nTaking " + book + " from " + bodyTokens[0] + "\n");

                    booksAndStatusLocker.lock();
                    booksAndStatus.at(book) = WAITING_FOR_BOOK;
                    booksAndStatusLocker.unlock();

                    connectionHandlerLocker.lock();
                    connectionHandler.sendLine(responseFrame);
                    connectionHandlerLocker.unlock();
                }
            } else if (bodyTokens[0] == "Taking") {
                if (username == bodyTokens[calculateBookLength(book) + 2]) {

                    booksAndStatusLocker.lock();
                    booksAndStatus.erase(book);
                    booksAndStatusLocker.unlock();

                    genrebooksMapLocker.lock();
                    genreBooksMap.erase(book);
                    genrebooksMapLocker.unlock();
                }
                else if (booksAndStatus.find(book) != booksAndStatus.end() && booksAndStatus.at(book) == WAITING_FOR_BOOK) {

                    booksAndStatusLocker.lock();
                    booksAndStatus.at(book) = OWN_BOOK;
                    booksAndStatusLocker.unlock();

                    genrebooksMapLocker.lock();
                    genreBooksMap.insert(std::pair<std::string, std::string>(book, genre));
                    genrebooksMapLocker.unlock();

                    borrowMapLocker.lock();
                    borrowMap.insert((std::pair<std::string, std::string>(book, bodyTokens[calculateBookLength(book) + 2])));
                    borrowMapLocker.unlock();
                }
            } else if (bodyTokens[0] == "Returning") {
                if (username == bodyTokens[calculateBookLength(book) + 2]) {

                    booksAndStatusLocker.lock();
                    booksAndStatus.insert(std::pair<std::string, int>(book, OWN_BOOK));
                    booksAndStatusLocker.unlock();

                    genrebooksMapLocker.lock();
                    genreBooksMap.insert(std::pair<std::string, std::string>(book, genre));
                    genrebooksMapLocker.unlock();

                } else if (booksAndStatus.find(book) != booksAndStatus.end() && booksAndStatus.at(book) == OWN_BOOK && borrowMap.find(book) != borrowMap.end() && borrowMap.at(book) == bodyTokens[calculateBookLength(book) + 2]) {

                    booksAndStatusLocker.lock();
                    booksAndStatus.erase(book);
                    booksAndStatusLocker.unlock();

                    borrowMapLocker.lock();
                    borrowMap.erase(book);
                    borrowMapLocker.unlock();

                    genrebooksMapLocker.lock();
                    genreBooksMap.erase(book);
                    genrebooksMapLocker.unlock();

                }
            } else if ((bodyTokens[0] == "Book" || bodyTokens[0] == "book") && bodyTokens[1] == "status") {
                responseFrame.append("SEND\ndestination:" + genre + "\n\n" + username + ":");

                genrebooksMapLocker.lock();
                if (!genreBooksMap.empty()) {
                    bool first = true;
                    for (std::pair<std::string, std::string> p : genreBooksMap) {
                        if (p.second == genre) {
                            if (first) {
                                responseFrame.append(p.first);
                                first = false;
                            } else {
                                responseFrame.append("," + p.first);
                            }
                        }
                    }
                }
                genrebooksMapLocker.unlock();

                connectionHandlerLocker.lock();
                connectionHandler.sendLine(responseFrame);
                connectionHandlerLocker.unlock();

            }
        } else if (tokens[0] == RECEIPT_FRAME) {
            std::string receiptStr = split(tokens[1], ':')[1];
            int receipt = std::atoi(receiptStr.c_str());
            if((reciptSubscriptionMap.at(receipt) == "login")) {
                std::cout << receiptToPrintInfoMap.at(receipt) << std::endl;
            }
            if (reciptSubscriptionMap.at(receipt) == "logout") {
                connectionHandler.close();
                connected = false;
            }
            else if(reciptSubscriptionMap.at(receipt) == "join") {
                std::cout << receiptToPrintInfoMap.at(receipt) << std::endl;
            }
            else if(reciptSubscriptionMap.at(receipt) == "exit") {
                std::cout << receiptToPrintInfoMap.at(receipt) << std::endl;
            }
        }
        else if (tokens[0] == ERROR_FRAME)
        {
            connectionHandler.close();
            connected = false;
        }
    }

    catch(std::exception e) {
        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$Exception thrown in server thread$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    }
}

std::vector<std::string>ServerThread::split(std::string &line, char delim) {
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

std::string ServerThread::parseBookName(std::string body) {
    bool firstElement = true;
    std::string book;
    std::vector<std::string> bodyTokens = split(body, ' ');

    if (bodyTokens[1] == "wish" || bodyTokens[1] == "has") {
        int index = 2;
        if (bodyTokens[1] == "has" && bodyTokens[2] == "added") index = 5;
        else if (bodyTokens[1] == "wish") index = 4;
        for (int i = index; i < (signed)bodyTokens.size(); i++) {
            if(firstElement == true)
            {
                book.append(bodyTokens[i]);
                firstElement = false;
            }
            else {
                book.append(" " + bodyTokens[i]);
            }
        }
    } else if (bodyTokens[0] == "Taking" || bodyTokens[0] == "Returning") {
        std::string stopPhrase;
        if (bodyTokens[0] == "Taking") stopPhrase = "from";
        else stopPhrase = "to";
        for (int i = 1; i < (signed)bodyTokens.size() && bodyTokens[i] != stopPhrase;  i++) {
            if(bodyTokens[i]!= "") {
                if (firstElement) {
                    book.append(bodyTokens[i]);
                    firstElement = false;
                } else {
                    book.append(" " + bodyTokens[i]);
                }
            }
        }
    }
    return book;
}

int ServerThread::calculateBookLength(std::string bookName) {
    return split(bookName,' ').size();
}

ServerThread::ServerThread(ConnectionHandler &connectionHandler, std::string &username,std::map<std::string, int> &booksAndStatus, std::map<int, std::string> &idGenreMap,
                           std::map<int, std::string> &reciptSubscriptionMap, std::map<std::string, std::string> &borrowMap,std::map<std::string,std::string>&genreBooksMap, std::map<int,std::string>& receiptToPrintInfoMap, bool& connected,
                           std::mutex& connectionHandlerLocker,
                           std::mutex& booksAndStatusLocker,
                           std::mutex& idGenreMapLocker,
                           std::mutex& reciptSubscriptionMapLocker,
                           std::mutex& borrowMapLocker,
                           std::mutex& genrebooksMapLocker,
                           std::mutex& reciptToPrintInfoMapLocker)  :
        connectionHandler(connectionHandler), username(username), booksAndStatus(booksAndStatus), idGenreMap(idGenreMap), reciptSubscriptionMap(reciptSubscriptionMap),
        borrowMap(borrowMap),genreBooksMap(genreBooksMap), receiptToPrintInfoMap(receiptToPrintInfoMap),responseFrame(""), connected(connected),
        connectionHandlerLocker(), booksAndStatusLocker(), idGenreMapLocker(), reciptSubscriptionMapLocker(), borrowMapLocker(), genrebooksMapLocker(), reciptToPrintInfoMapLocker()
{}
