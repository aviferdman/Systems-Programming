//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#ifndef EXAMPLE4_USER_H
#define EXAMPLE4_USER_H
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "Watchable.h"

class Watchable;
class Session;

class User {
public:

    User (std::string  name);

    //Rule of 5
    User& operator=(const User &other);
    User(const User& other);
    virtual ~User();
    User(User&& other);
    User& operator=(User &&other);
    //

    void clear();
    virtual Watchable* getRecommendation(Session& s) = 0;
    virtual User* copyMe() const = 0;
    std::vector<Watchable*> get_history() const;
    virtual User* dup (std::string name)=0;
    void  addToHistoryList(Watchable* w);
    std::string getName() const;
    bool HistoryContains(Watchable& w);
protected:
    std::vector<Watchable*> history;
private:
    const std::string name;
};

class LengthRecommenderUser : public User {
public:


    LengthRecommenderUser(const std::string &name);

    //Rule of 5
    virtual LengthRecommenderUser& operator=(const LengthRecommenderUser& other);
    LengthRecommenderUser(const LengthRecommenderUser& other);
    LengthRecommenderUser(LengthRecommenderUser&& other);
    LengthRecommenderUser& operator=(LengthRecommenderUser &&other);
    virtual ~LengthRecommenderUser();
    //


    virtual User* copyMe() const;
    virtual User* dup (std::string name);
    virtual Watchable* getRecommendation(Session& s);
private:
};

class RerunRecommenderUser : public User {
public:


    RerunRecommenderUser(const std::string &name);

    //Rule of 5
    virtual RerunRecommenderUser& operator=(const RerunRecommenderUser& other);
    RerunRecommenderUser(const RerunRecommenderUser& other);
    RerunRecommenderUser(RerunRecommenderUser&& other);
    RerunRecommenderUser& operator=(RerunRecommenderUser &&other);
    virtual ~RerunRecommenderUser();
    //


    virtual User* copyMe() const;
    virtual User* dup (std::string name);
    virtual Watchable* getRecommendation(Session& s);
    int get_Index_Of_Last_Recommended();
    void set_Index_Of_Last_Recommended(int index);
private:
    int index_of_last_recommended_watchable;
};

class GenreRecommenderUser : public User {
public:


    GenreRecommenderUser(const std::string &name);

    //Rule of 5
    virtual GenreRecommenderUser& operator=(const GenreRecommenderUser& other);
    GenreRecommenderUser(const GenreRecommenderUser& other);
    GenreRecommenderUser(GenreRecommenderUser&& other);
    GenreRecommenderUser& operator=(GenreRecommenderUser &&other);
    virtual ~GenreRecommenderUser();
    //


    virtual User* copyMe() const;
    virtual User* dup (std::string name);
    virtual Watchable* getRecommendation(Session& s);
private:
};
#endif //EXAMPLE4_USER_H