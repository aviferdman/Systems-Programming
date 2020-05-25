
//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#include "../include/Session.h"
#include "../include/User.h"
#include "../include/Watchable.h"
#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include "../include/Action.h"

#define  CREATE_USER "createuser"
#define  CHANGE_ACTIVE_USER "changeuser"
#define  DELETE_USER "deleteuser"
#define  DUPLICATE_USER "dupuser"
#define  PRINT_CONTENT_LIST "content"
#define  PRINT_WATCH_HISTORY "watchhist"
#define  WATCH "watch"
#define  PRINT_ACTIONS_LOG "log"
#define  EXIT "exit"
#define  NEXT_EPISODE_DOES_NOT_EXIST -1

using  namespace std;


Session::Session(const std::string &configFilePath): content(), userMap(), actionsLog(), activeUser(), input1(""), input2("") {
    string s = "default";
    this->activeUser = new LengthRecommenderUser(s);
    std::pair<std::string,User*> pair (s,this->activeUser);
    userMap.insert(pair);
    parseJson(configFilePath);
}
//Rule of 5
Session& Session::operator=(const Session & other) {
    if(this != &other) {
        clear();
        for (int i = 0; i <(signed) other.actionsLog.size(); i=i+1) {
            BaseAction* b = other.actionsLog[i]->copyMe();
            this->actionsLog.push_back(b);
        }
        this->input1 = other.activeUser->getName();
        //this->activeUser = other.activeUser;
        auto iterator = other.userMap.begin();
        while (iterator != other.userMap.end()) {
            string s = iterator -> first;
            User* u = iterator->second->copyMe();
            std::pair<std::string,User*> pair (s,u);
            userMap.insert(pair);
            if(iterator -> first == input1){
                this->activeUser = u;
            }
            iterator ++;
        }

        for (int i = 0; i < (signed)other.content.size(); i=i+1) {
            Watchable* w = other.content[i]->copyMe();
            this->content.push_back(w);
        }
    }
    return *this;
}

Session::Session(Session &session):content(), userMap(), actionsLog(), activeUser(), input1(""), input2("") {
    for (int i = 0; i <(signed) session.getActions().size(); i=i+1) {
        BaseAction* b = session.getActions()[i]->copyMe();
        this->actionsLog.push_back(b);
    }
    this->activeUser = session.getActiveUser()->copyMe();
    auto iterator = session.userMap.begin();
    std::pair<std::string,User*> pair (activeUser->getName(),this->activeUser);
    userMap.insert(pair);
    while (iterator != session.userMap.end()) {
        if(iterator->second->getName() != activeUser->getName()) {
            string s = iterator->first;
            User *u = iterator->second->copyMe();
            std::pair<std::string, User *> x(s, u);
            userMap.insert(x);
        }
        iterator++;
    }
    for (int i = 0; i <(signed) session.getContent().size(); i=i+1) {
        Watchable* w = session.getContent()[i]->copyMe();
        this->content.push_back(w);
    }
}
Session::~Session() {
    clear();
}

Session::Session(Session &&other):content(other.content),userMap(other.userMap), actionsLog(other.actionsLog),activeUser(other.activeUser), input1(other.input1), input2(other.input2) {
    other.activeUser = nullptr;
    for (int i = 0; i <(signed)other.getActions().size(); i=i+1) {
        other.actionsLog[i] = nullptr;
    }
    auto iterator = other.userMap.begin();
    while (iterator != other.userMap.end()) {
        iterator->second = nullptr;
        iterator ++;
    }
    for (int i = 0; i <(signed) other.getContent().size(); i=i+1) {
        other.content[i] = nullptr;
    }
}
Session& Session::operator=(Session &&other) {
    if(this!=&other){
        clear();
        for (int i = 0; i <(signed) other.getActions().size(); i=i+1) {
            BaseAction* b = other.getActions()[i]->copyMe();
            this->actionsLog.push_back(b);
            other.actionsLog[i] = nullptr;
        }
        this->input1 = other.activeUser->getName();
        //this->activeUser = other.getActiveUser()->copyMe();
        auto iterator = other.userMap.begin();
        while (iterator != other.userMap.end()) {
            string s = iterator -> first;
            User* u = iterator->second->copyMe();
            std::pair<std::string,User*> pair (s,u);
            userMap.insert(pair);
            if(iterator -> first == input1){
                this->activeUser = u;
            }
            iterator->second = nullptr;
            iterator ++;
        }

        for (int i = 0; i < (signed)other.getContent().size(); i=i+1) {
            Watchable* w = other.getContent()[i]->copyMe();
            this->content.push_back(w);
            other.content[i] = nullptr;
        }
    }
    return *this;
}
//

void Session::clear(){
    for (const auto& user: userMap) {
        delete user.second;
    }
    userMap.clear();

    for (int i = 0; i <(signed) this->getContent().size(); i=i+1) {
        if(content[i] != nullptr) {
            delete (content[i]);
        }
    }
    content.clear();

    for(int i = 0; i <(signed) this->getActions().size(); i++) {
        delete actionsLog[i];
    }
    actionsLog.clear();
}
void Session::start() {
    cout << "SPLFLIX is now on!" << endl;
    string str;
    vector<string> tokens;
    int first = 0;
    int last = 0;
    int index = 0;
    while (true) {

        getline(cin, str);
        last = str.find(' ');
        if (last == (int)string::npos) { // one word command
            tokens.insert(tokens.begin(), str);
        } else {
            while (last != (int)string::npos) {
                last = str.find(' ');
                tokens.insert(tokens.begin() + index, str.substr(0, last));
                index++;
                first = last;
                str = str.substr(first + 1);
            }
        }

        index = 0; // for next time

        if ((tokens[0] == CREATE_USER)) {
            // Check if user with same name exists and check if algo is legal
            if(tokens.size()==3)
            {
                if (this->userMap.end() == this->userMap.find(tokens[1]))
                {
                    if (((tokens[2] == "len") || tokens[2] == "rer" || tokens[2] == "gen"))
                    {
                        input1 = (tokens[1]);
                        input2 = (tokens[2]);
                        BaseAction *action = new CreateUser();
                        action->act(*this);
                        this->actionsLog.push_back(action);
                    }
                    else
                    {
                        BaseAction *action = new CreateUser();
                        action->setStatus(ERROR);
                        action->setErrorMessage(" Illegal algo");
                        this->actionsLog.push_back(action);
                        cout << "ERROR - Illegal algo" << endl;
                    }
                }
                else
                {
                    BaseAction *action = new CreateUser();
                    action->setStatus(ERROR);
                    action->setErrorMessage(" user with same name exist");
                    this->actionsLog.push_back(action);
                    cout << "Error - user with same name exist" << endl;
                }
            }
            else
            {
                BaseAction *action = new CreateUser();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }
        }

        else if ((tokens[0] == CHANGE_ACTIVE_USER)) {
            // add user map contains user
            if(tokens.size()==2)
            {
                if(UserMapContains(tokens[1]))
                {
                    input1 = (tokens[1]);
                    BaseAction *action = new ChangeActiveUser();
                    action->act(*this);
                    this->actionsLog.push_back(action);
                }
                else
                {
                    BaseAction *action = new ChangeActiveUser();
                    action->setStatus(ERROR);
                    action->setErrorMessage(" username does not exist");
                    this->actionsLog.push_back(action);
                    cout << "Error - username does not exist" << endl;
                }
            }

            else
            {
                BaseAction *action = new ChangeActiveUser();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }
        }
        else if ((tokens[0] == DELETE_USER)) {
            // add user map contains user
            if(tokens.size()==2)
            {
                if(UserMapContains(tokens[1]))
                {
                    input1 = tokens[1];
                    BaseAction *action = new DeleteUser();
                    action->act(*this);
                    this->actionsLog.push_back(action);
                }
                else
                {
                    BaseAction *action = new DeleteUser();
                    action->setStatus(ERROR);
                    action->setErrorMessage(" username does not exist");
                    this->actionsLog.push_back(action);
                    cout << "Error - username does not exist" << endl;
                }
            }
            else
            {
                BaseAction *action = new DeleteUser();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }
        }
        else if ((tokens[0] == DUPLICATE_USER)) {
            // add user map contains original user and does not contains new user
            if(tokens.size()==3)
            {
                if (UserMapContains(tokens[1]) && !UserMapContains(tokens[2]))
                {
                    this->input1 = tokens[1];
                    this->input2 = tokens[2];
                    BaseAction *action = new DuplicateUser();
                    action->act(*this);
                    this->actionsLog.push_back(action);
                }
                else if (UserMapContains(tokens[2]))
                {
                    BaseAction *action = new DuplicateUser();
                    action->setStatus(ERROR);
                    action->setErrorMessage(" username is already in use");
                    this->actionsLog.push_back(action);
                    cout << "Error - username is already in use" << endl;
                } else if (!UserMapContains(tokens[1])){
                    BaseAction *action = new DuplicateUser();
                    action->setStatus(ERROR);
                    action->setErrorMessage(" username doesn't exist");
                    this->actionsLog.push_back(action);
                    cout << "Error - username doesn't exist" << endl;
                }
            }
            else
            {
                BaseAction *action = new DuplicateUser();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }

        } else if ((tokens[0] == PRINT_CONTENT_LIST)) {
            if(tokens.size()==1) {
                BaseAction *action = new PrintContentList();
                action->act(*this);
                this->actionsLog.push_back(action);
            } else{
                BaseAction *action = new PrintContentList();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }
        } else if ((tokens[0] == PRINT_WATCH_HISTORY)) {
            if(tokens.size()==1) {
                BaseAction *action = new PrintWatchHistory();
                action->act(*this);
                this->actionsLog.push_back(action);
            } else{
                BaseAction *action = new PrintWatchHistory();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }

        } else if ((tokens[0] == WATCH)) {
            // id of watch is legal ( id <= content.size() )
            if(tokens.size()==2) {
                int watchIdIndex = stoi(tokens[1]);
                if ( watchIdIndex >= 1 && watchIdIndex <= (signed)content.size())
                {
                    input1 = tokens[1];
                    BaseAction *action = new Watch();
                    action->act(*this);
                    string yesOrNo;
                    do{
                        getline(cin,yesOrNo);
                        if(yesOrNo == "n")
                            break;
                        else if (yesOrNo == "y") {
                            action = new Watch();
                            action -> act(*this);
                        }
                    }while(true);
                }
                else
                {
                    BaseAction *action = new Watch();
                    action->setStatus(ERROR);
                    action->setErrorMessage(" illegal watch id index");
                    this->actionsLog.push_back(action);
                    cout << "Error - illegal watch id index" << endl;
                }
            }
            else {
                BaseAction *action = new Watch();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }

        } else if ((tokens[0] == PRINT_ACTIONS_LOG)) {
            if(tokens.size()==1) {
                BaseAction *action = new PrintActionsLog();
                action->act(*this);
                this->actionsLog.push_back(action);
            } else{
                BaseAction *action = new PrintActionsLog();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }

        } else if ((tokens[0] == EXIT)) {
            if(tokens.size()==1) {
                BaseAction *action = new Exit();
                action->act(*this);
                this->actionsLog.push_back(action);
                break;
            } else{
                BaseAction *action = new Exit();
                action->setStatus(ERROR);
                action->setErrorMessage(" illegal input");
                this->actionsLog.push_back(action);
                cout << "Error - illegal input" << endl;
            }
        }
        tokens.clear();
    }
}

void Session::setInput1(std::string newInput1) {
    this->input1 = std::move(newInput1);
}

std::string Session:: getInput1() const {
    return input1;
}
std::string Session:: getInput2() const {
    return input2;
}

void Session:: add_User (User* user){
    this->userMap.insert(std::pair<string,User*>(user->getName(), user));
}
void Session:: change_Active_User(User* user){
    this->activeUser = user;
}
std::unordered_map<std::string,User*>* Session::getUsers(){
    return &userMap;
}
const std::vector<Watchable*>& Session::getContent() {
    return content;
}

Watchable* Session::findContentByID(int i) {
    return content[i-1];
}
User* Session::getActiveUser() {
    return activeUser;
}
const std::vector<BaseAction*>& Session::getActions() {
    return this->actionsLog;
}

void Session::addAction(BaseAction *baseAction) {
    this->actionsLog.push_back(baseAction);
}

bool Session::UserMapContains(string username) {
    for (const auto& user : userMap)
    {
        if(user.first == username) {
            return true;
        }
    }
    return false;
}

void Session::parseJson(const std::string &configFilePath) {

    int id = 1;

    std::ifstream i(configFilePath);
    json j;
    i >> j;

    int movie = 0;

    while (j["movies"][movie] != nullptr) {

        int length = (j["movies"][movie]["length"]);

        string name = j["movies"][movie]["name"];

        vector<string> tags;
        int tag = 0;
        while (j["movies"][movie]["tags"][tag] != nullptr) {
            tags.push_back(j["movies"][movie]["tags"][tag]);
            tag++;
        }
        Watchable *w1 = new Movie(id, name, length, tags);
        id++;
        this->content.push_back(w1);
        movie++;

    }

    int tv_show = 0;
    while (j["tv_series"][tv_show] != nullptr) {
        string tv_name = j["tv_series"][tv_show]["name"];
        int episode_length = j["tv_series"][tv_show]["episode_length"];
        vector<string> tags;
        int tag = 0;
        while (j["tv_series"][tv_show]["tags"][tag] != nullptr) {
            tags.push_back(j["tv_series"][tv_show]["tags"][tag]);
            tag++;
        }
        //string tagsStr(tags.begin(),tags.end());
        int season = 0;
        while (j["tv_series"][tv_show]["seasons"][season] != nullptr) {
            int num_of_episodes = j["tv_series"][tv_show]["seasons"][season];
            for (int h = 0; h < num_of_episodes; h++) {
                if(h < num_of_episodes - 1 || (j["tv_series"][tv_show]["seasons"][season + 1] != nullptr )) { // next episode / season exist
                    Watchable *w1;
                    w1 = new Episode(id, tv_name, episode_length, season + 1, h + 1, tags);
                    this->content.push_back(w1);
                }
                else {
                    Watchable *w1 = new Episode(id, tv_name, episode_length, season + 1, h + 1, tags,NEXT_EPISODE_DOES_NOT_EXIST);
                    this->content.push_back(w1);
                }
                id++;
            }
            season++;
        }
        tv_show++;
    }
}

