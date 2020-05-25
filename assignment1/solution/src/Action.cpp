//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#include "../include/Action.h"
#include "../include/User.h"
#include "../include/Session.h"
#define  Length_Recommender "len"
#define  Rerun_Recommender "rer"
#define  Similar_Genre "gen"
#include <iostream>
#include <sstream>
#include <utility>

BaseAction::BaseAction():errorMsg(""), status(PENDING) {
}

BaseAction::~BaseAction() = default;

void BaseAction::complete() {
    this->status = COMPLETED;
}

void BaseAction::error(const std::string &string1) {
    this->status = ERROR;
    this->errorMsg = string1;
}

ActionStatus BaseAction::getStatus() const {
    return this->status;
}

std::string BaseAction::getErrorMsg() const {
    return this->errorMsg;
}

void BaseAction::setStatus(ActionStatus newStatus){
    this->status = newStatus;
}

void BaseAction::setErrorMessage(std::string newErrorMsg) {
    this->errorMsg = std::move(newErrorMsg);
}


void CreateUser::act(Session &sess) {
    if (sess.getInput2()==Length_Recommender){
        auto* u = new LengthRecommenderUser(sess.getInput1());
        sess.add_User(u);
        //sess.change_Active_User(u);
        this->complete();
    } else if (sess.getInput2()==Rerun_Recommender){
        auto* u = new RerunRecommenderUser(sess.getInput1());
        sess.add_User(u);
        //sess.change_Active_User(u);
        this->complete();
    } else if(sess.getInput2()==Similar_Genre){
        auto u = new GenreRecommenderUser(sess.getInput1());
        sess.add_User(u);
        //sess.change_Active_User(u);
        this->complete();
    }
    else{
        this->error(" user creation is illegal failed");
    }
}
std::string CreateUser::toString() const {
    string s = "Create new User";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";
}

BaseAction* CreateUser::copyMe() const {
    BaseAction* base = new CreateUser();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}

void ChangeActiveUser::act(Session &sess) {
    std::unordered_map<std::string,User*>* users= sess.getUsers();
    std::string userToFind = sess.getInput1();
    User* u;
    try {
        if (users->find(userToFind) != users->end()) { // user found
            u = users->at(userToFind);
            sess.change_Active_User(u);
            complete();
        }
        else {
            this->error(" user not found failed");
        }
    }
    catch (const std::exception& e){
        this->error(" failed");
    }
}
std::string ChangeActiveUser::toString() const {
    string s = "Change active User";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}


BaseAction* ChangeActiveUser::copyMe() const {
    BaseAction* base = new ChangeActiveUser();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}

void DeleteUser::act(Session &sess) {
    std::unordered_map<std::string,User*>* users= sess.getUsers();
    std::string userToDelete = sess.getInput1();
    try {
        if (users->find(userToDelete) != users->end()) { // user found
            User *u = users->at(userToDelete);
            delete (u);
            users->erase(userToDelete);
            complete();
        } else{
            this->error(" user not found");
        }
    } catch(const std::exception& e){
        this->error(" failed");
    }
}
std::string DeleteUser::toString() const {
    string s = "Delete User";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}


BaseAction* DeleteUser::copyMe() const {
    BaseAction* base = new DeleteUser();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}

void DuplicateUser::act(Session &sess) {

    try {
        std::unordered_map<std::string,User*>* users= sess.getUsers();
        User* u = users->at(sess.getInput1())->dup(sess.getInput2());
        //u = users->at(sess.getInput1());
        for (int i = 0; i < (int) sess.getActiveUser()->get_history().size(); ++i) {
            Watchable* w = (sess.getActiveUser()->get_history()[i]->copyMe());
            u->addToHistoryList(w);
        }
        sess.add_User(u);
        complete();

    } catch(const std::exception& e){
        this->error(" failed");
    }
}

std::string DuplicateUser::toString() const {
    string s = "Duplicate User";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}


BaseAction* DuplicateUser::copyMe() const {
    BaseAction* base = new DuplicateUser();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}


void PrintContentList::act(Session &sess) {
    try {
        string s;
        vector<Watchable *> listW = sess.getContent();
        for (int i = 0; i < (int)listW.size(); ++i) {
            cout << listW[i]->toString() << endl;
        }
        complete();
        //u=users->at(userToDelete);
    }catch(const std::exception& e){
        this->error(" failed");
    }
}
std::string PrintContentList::toString() const {
    string s = "Print content list";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}


BaseAction* PrintContentList::copyMe() const {
    BaseAction* base = new PrintContentList();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}


void PrintWatchHistory::act(Session &sess) {
    try {
        int index = 1;
        for (int i = 0; i <(int) sess.getActiveUser()->get_history().size(); ++i) {
            std::string out_string;
            std::stringstream ss;
            ss << index;
            out_string = ss.str();
            string s = out_string+". "+sess.getActiveUser()->get_history()[i]->stringForWatching();
            cout << s << endl;
            index = index +1;
        }
        complete();
    }catch(const std::exception& e){
        this->error(" failed");
    }
}
std::string PrintWatchHistory::toString() const {
    string s = "Print watch history";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}



BaseAction* PrintWatchHistory::copyMe() const {
    BaseAction* base = new PrintWatchHistory();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}


void Watch::act(Session &sess) {
    string yesOrNo;
    try {
        if((signed)sess.getContent().size()>=(signed)std::stoi(sess.getInput1())&&(signed)std::stoi(sess.getInput1())>(signed)0) {
            Watchable *w = sess.findContentByID(std::stoi(sess.getInput1()))->copyMe();
            sess.getActiveUser()->addToHistoryList(w);
            cout << "Watching " + w->stringForWatching() << endl;
            complete();
            sess.addAction(this);
            Watchable *w1 = w->getNextWatchable(sess);
            if (w1 == nullptr)
            {
                w1 = sess.getActiveUser()->getRecommendation(sess);
                if(w1 == nullptr) { // nothing to recommend
                    cout << "nothing to recommend" << endl;
                }
                else {
                    cout << "we recommend to watch " + w1->stringForWatching() + " Continue Watching[y/n]" << endl;
                }

            }
            else
            {
                cout << "we recommend to watch " + w1->stringForWatching() + " Continue Watching[y/n]" << endl;
            }
            sess.setInput1(to_string(w1->getId()));
        }
        else {
            this->error(" content out of range error");
            sess.addAction(this);
        }
    }
    catch(const std::exception& e){
        this->error(" failed");
    }
}
std::string Watch::toString() const {
    string s = "Watch";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}

BaseAction* Watch::copyMe() const {
    BaseAction* base = new Watch();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}


void PrintActionsLog::act(Session &sess) {
    try {

        for (int i = (int)sess.getActions().size() - 1; i>=0 ; i--) {
            cout << sess.getActions()[i]->toString() << endl;
        }
        complete();
    } catch(const std::exception& e){
        this->error(" failed");
    }
}
std::string PrintActionsLog::toString() const {
    string s = "Print actions log";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}


BaseAction* PrintActionsLog::copyMe() const {
    BaseAction* base = new PrintActionsLog();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}


void Exit::act(Session &sess) {
    complete();
}
std::string Exit::toString() const {
    string s = "Exit ";
    if((this->getStatus()) == COMPLETED) {
        return s.append(" COMPLETED");
    }
    if((this->getStatus()) == ERROR) {
        return s.append(this->getErrorMsg()).append(" ERROR");
    }
    return "";}

BaseAction* Exit::copyMe() const {
    BaseAction* base = new Exit();
    base->setErrorMessage(this->getErrorMsg());
    base->setStatus(this->getStatus());
    return base;
}
