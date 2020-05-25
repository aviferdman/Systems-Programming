//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#ifndef EXAMPLE4_SESSION_H
#define EXAMPLE4_SESSION_H

#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include "json.hpp"
#include "Action.h"

using json = nlohmann::json;


class User;
class Watchable;


class Session {
public:

    //Role of 5
    Session(const std::string &configFilePath);
    Session(Session &session);
    ~Session();
    Session(Session&& other);
    Session& operator=(Session &&other);
    //

    Session& operator=(const Session&);
    std::string getInput1() const ;
    std::string getInput2() const ;
    void setInput1(std::string newInput1);
    void add_User (User* user);
    void change_Active_User(User* user);
    User* getActiveUser();
    std::unordered_map<std::string,User*>* getUsers();
    const std::vector<Watchable*>& getContent();
    const std::vector<BaseAction*>& getActions();
    void addAction(BaseAction* baseAction);
    Watchable* findContentByID(int i);
    void clear();
    void start();
    bool UserMapContains(std::string username);

private:
    void parseJson(const std::string &configFilePath);
    void printContent();
    std::vector<Watchable*> content;
    std::unordered_map<std::string,User*> userMap;
    std::vector<BaseAction*> actionsLog;
    User* activeUser;
    std::string input1;
    std::string input2;
};


#endif //EXAMPLE4_SESSION_H