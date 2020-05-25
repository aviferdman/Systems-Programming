//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#include "../include/User.h"
#include <iostream>
#include <utility>

using  namespace std;

User::User(string name):history(), name(std::move(name)) {}

//Rule of 5
User& User::operator=(const User &other) {
    if(this != &other) {
        clear();
        for (int i = 0; i < (int) other.history.size(); i = i + 1) {
            if (other.history[i]) {
                addToHistoryList(other.history[i]);
            }
        }
    }
    return *this;
}
User::User(const User &other): history(), name(other.name) {
    for (int i = 0; (unsigned) i < (unsigned)other.get_history().size(); i=i+1) {
        Watchable* watch = get_history()[i]->copyMe();
        addToHistoryList(watch);
    }
}
User::~User() {
    for (int i=0; i<(int)this->get_history().size(); i=i+1){
        if(history[i]!= nullptr) {
            delete (history[i]);
        }
    }
}
User::User(User &&other): history(other.history), name(other.name) {
    if(&other!=this) {
        for (int i = 0; i < (int)other.get_history().size(); i = i + 1) {
            if (other.get_history()[i]) {
                (other.get_history()[i]) = nullptr;
            }
        }
    }
}
User& User::operator=(User &&other) {
    if (this != &other) {
        clear();
        for (int i = 0; i < (int)other.get_history().size(); i = i + 1) {
            if (other.get_history()[i]) {
                addToHistoryList(other.get_history()[i]);
                other.get_history()[i] = nullptr;
            }
        }
    }
    return *this;
}
//

void User::clear() {
    for (int i=0; i<(int)this->get_history().size(); i=i+1){
        if(history[i]) {
            delete (history[i]);
        }
    }
}

string User::getName() const {
    return name;
}

std::vector<Watchable*> User::get_history() const {
    return this->history;
}

void User::addToHistoryList(Watchable* w) {
    this->history.push_back(w);
}

bool User::HistoryContains(Watchable& w) {
    for(int i=0; i < (int) this->get_history().size(); i = i + 1) {
        if(this->get_history().at(i)->getId() == w.getId()) {
            return true;
        }
    }
    return false;
}

LengthRecommenderUser::LengthRecommenderUser(const std::string &name):User(name) {}

//Rule of 5
LengthRecommenderUser& LengthRecommenderUser::operator=(const LengthRecommenderUser &other) {
    if(this != &other) {
        clear();
        for (int i = 0; i < (int) other.get_history().size(); i = i + 1) {
            Watchable *w = other.get_history()[i]->copyMe();
            this->addToHistoryList(w);
        }
    }
    return *this;
}
LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &other):User(other) {}
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser &&other):User(other) {}
LengthRecommenderUser& LengthRecommenderUser::operator=(LengthRecommenderUser &&other) {
    if (this != &other)
    {
        clear();
        for (int i = 0; i <(int) other.get_history().size(); i = i + 1) {
            if (other.get_history()[i]) {
                addToHistoryList(other.get_history()[i]);
                other.get_history()[i] = nullptr;
            }
        }
    }
    return *this;
}
LengthRecommenderUser::~LengthRecommenderUser(){
}
//

User* LengthRecommenderUser::dup(std::string name) {
    return new LengthRecommenderUser(name);
}
User* LengthRecommenderUser::copyMe() const {
    User* w = new LengthRecommenderUser(this->getName());
    for (int i = 0; i < (int)get_history().size(); ++i) {
        Watchable* watch = get_history()[i]->copyMe();
        w->addToHistoryList(watch);
    }
    return w;
}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) { // len recommendation
    int sum = 0, counter = 0;
    double avg;

    int index_of_watchable_to_recommend = -1;
    double min_length_difference = INFINITY;

    for(int i=0; i < (int)history.size();i++){
        sum = sum + history.at(i)->getLength();
        counter++;
    }

    avg = (double)sum / (double)counter;

    for(int i=0; i <(int) s.getContent().size();i++) {
        if (abs(s.getContent().at(i)->getLength() - avg) < min_length_difference && !(HistoryContains(*(s.getContent().at(i))))) {
            index_of_watchable_to_recommend = i;
            min_length_difference = abs(s.getContent().at(i)->getLength() - avg);
        }
    }

    if(index_of_watchable_to_recommend == -1) {
        return nullptr;
    }

    return s.getContent().at(index_of_watchable_to_recommend);
}



RerunRecommenderUser::RerunRecommenderUser(const std::string &name):User(name), index_of_last_recommended_watchable(0) {}

//Rule of 5
RerunRecommenderUser& RerunRecommenderUser::operator=(const RerunRecommenderUser &other) {
    if(this != &other) {
        clear();
        for (int i = 0; i < (int) other.get_history().size(); i = i + 1) {
            Watchable *w = other.get_history()[i]->copyMe();
            this->addToHistoryList(w);
        }
    }
    return *this;
}
RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &other):User(other), index_of_last_recommended_watchable(other.index_of_last_recommended_watchable) {}
RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser &&other):User(other),index_of_last_recommended_watchable(other.index_of_last_recommended_watchable) {}
RerunRecommenderUser& RerunRecommenderUser::operator=(RerunRecommenderUser &&other) {
    if (this != &other)
    {
        clear();
        for (int i = 0; i < (int)other.get_history().size(); i = i + 1) {
            if (other.get_history()[i]) {
                addToHistoryList(other.get_history()[i]);
                other.get_history()[i] = nullptr;
            }
        }
    }
    this->index_of_last_recommended_watchable = other.index_of_last_recommended_watchable;
    other.index_of_last_recommended_watchable = 0;
    return *this;
}
RerunRecommenderUser::~RerunRecommenderUser() {
}
//



User* RerunRecommenderUser::dup(std::string name) {
    return new RerunRecommenderUser(name);
}
User* RerunRecommenderUser::copyMe() const {
    RerunRecommenderUser* w = new RerunRecommenderUser(this->getName());
    w->set_Index_Of_Last_Recommended(this->index_of_last_recommended_watchable);
    for (int i = 0; i < (int)get_history().size(); ++i) {
        Watchable* watch = get_history()[i]->copyMe();
        w->addToHistoryList(watch);
    }
    return w;
}

int RerunRecommenderUser::get_Index_Of_Last_Recommended() {
    return this->index_of_last_recommended_watchable;
}
void RerunRecommenderUser::set_Index_Of_Last_Recommended(int index) {
    this->index_of_last_recommended_watchable=index;
}

Watchable* RerunRecommenderUser::getRecommendation(Session &s) {
    return history.at(index_of_last_recommended_watchable++ % history.size());
}






GenreRecommenderUser::GenreRecommenderUser(const std::string &name):User(name) {}

//Rule of 5
GenreRecommenderUser& GenreRecommenderUser::operator=(const GenreRecommenderUser &other) {
    if(this != &other) {
        clear();
        for (int i = 0; i < (int) other.get_history().size(); i = i + 1) {
            Watchable *w = other.get_history()[i]->copyMe();
            this->addToHistoryList(w);
        }
    }
    return *this;
}
GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &other):User(other) {}
GenreRecommenderUser::GenreRecommenderUser(GenreRecommenderUser &&other):User(other) {}
GenreRecommenderUser& GenreRecommenderUser::operator=(GenreRecommenderUser &&other){
    if (this != &other)
    {
        clear();
        for (int i = 0; i < (int)other.get_history().size(); i = i + 1) {
            if (other.get_history()[i]) {
                addToHistoryList(other.get_history()[i]);
                other.get_history()[i] = nullptr;
            }
        }
    }
    return *this;}
GenreRecommenderUser::~GenreRecommenderUser(){
}
//





User* GenreRecommenderUser::dup(std::string name) {
    return new GenreRecommenderUser(name);
}

User* GenreRecommenderUser::copyMe() const {
    GenreRecommenderUser* w = new GenreRecommenderUser(this->getName());
    for (int i = 0; i < (int)get_history().size(); ++i) {
        Watchable* watch = get_history()[i]->copyMe();
        w->addToHistoryList(watch);
    }
    return w;
}

Watchable* GenreRecommenderUser::getRecommendation(Session &s)
{
    map<string, int> tagsPopularity;

    int maxNumberOfAppearences = -1;
    string mostPopularTag;


    // Parse history into map

    for(auto & i : history) {
        for (int j = 0; j < (int)i->getTags().size(); j++) {
            if (tagsPopularity.find(i->getTags().at(j)) != tagsPopularity.end()) // tag exist
            {
                tagsPopularity[i->getTags().at(j)] += 1;
            } else { // tag does not exist
                tagsPopularity.insert(pair<string, int>(i->getTags().at(j), 1));
            }
        }
    }


    while(!tagsPopularity.empty()){

        pair < string, int> chosenPopularTag("",-1*INFINITY);

        // Find most popular tag

        for (pair<std::string, int> element : tagsPopularity) {
            if (element.second > maxNumberOfAppearences) {
                maxNumberOfAppearences = element.second;
                chosenPopularTag.first = element.first;
                chosenPopularTag.second = element.second;
            }
        }


        // Try to recommend with most popular tag

        for(int i=0; i< (int)s.getContent().size();i++) {
            if (s.getContent()[i]->getTagsStr().find(chosenPopularTag.first) != std::string::npos && !HistoryContains(*s.getContent()[i])) { // not found in history
                    return s.getContent()[i];
            }
        }

        // erase most popular

        tagsPopularity.erase(chosenPopularTag.first);
        maxNumberOfAppearences = -1;
    }
    return nullptr;
}