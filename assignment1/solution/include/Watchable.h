//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#ifndef EXAMPLE4_WATCHABLE_H
#define EXAMPLE4_WATCHABLE_H

#include <string>
#include <vector>

#include "Session.h"

using namespace std;
class Watchable {
public:

    Watchable(long id, int length, const std::vector<std::string>& tags);

    //rule of 3
    Watchable(const Watchable& other);
    virtual Watchable& operator=(const Watchable &other);
    virtual ~Watchable();
    //

    virtual std::string toString() const = 0;
    virtual std::string toStringWithoutID() const = 0;
    virtual std::string stringForWatching() const = 0;
    virtual Watchable* copyMe() const = 0;
    long getId() const;
    int getLength() const;
    string getTagsStr() const;
    vector<string> getTags() const;
    virtual string getName() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    void setTags(std::vector<std::string> newTags);
    void setLength(int newLength);
private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable {
public:
    Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags);

    //rule of 3
    Movie(const Movie &other);
    Movie& operator=(const Movie &other);
    ~Movie();
    //

    virtual Watchable* copyMe() const;
    virtual std::string toString() const;
    virtual std::string stringForWatching() const;
    virtual std::string toStringWithoutID() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
    virtual string getName() const;;
private:
    Movie(long id, int length, const vector<std::string> &tags, const Movie &other);
    std::string name;
};

class Episode : public Watchable {
public:

    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags, int nextEpisodeId);

    //rule of 3
    Episode(const Episode& other);
    Episode& operator=(const Episode &other);
    ~Episode();
    //

    virtual Watchable* copyMe() const;
    virtual std::string toString() const;
    virtual std::string stringForWatching() const;
    virtual std::string toStringWithoutID() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
    void Set_next_Episode_ID(int next);
    virtual string getName() const;
    long get_Next_Episode_ID();
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;

};

#endif //EXAMPLE4_WATCHABLE_H