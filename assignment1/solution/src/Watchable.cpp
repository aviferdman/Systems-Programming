//
// Created by ferdmaa@wincs.cs.bgu.ac.il on 20/11/2019.
//

#include "../include/Watchable.h"
#include <iostream>
using namespace std;

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags): id(id),length(length), tags(tags)  {}

//Rule of 3
Watchable:: Watchable(const Watchable& other) : id(other.id), length(other.length), tags(other.tags){}

Watchable& Watchable::operator=(const Watchable &other) {
    length = other.length;
    tags.clear();
    for (int i = 0; i <(int) other.tags.size(); ++i) {
        tags.push_back(other.tags[i]);
    }
    return *this;
}

Watchable::~Watchable() {}
//



vector<string> Watchable::getTags() const {
    return tags;
}

void Watchable::setLength(int newLength) {
    this->length = newLength;
}

void Watchable::setTags(std::vector<std::string> newTags) {
    for (int i = 0; i < (int)newTags.size(); ++i) {
        tags.push_back(newTags[i]);
    }
}

long Watchable::getId() const { return this->id;}

int Watchable::getLength() const {return this->length;}

string Watchable::getTagsStr() const {
    string retVal = "";
    retVal.append("[");
    for (int i = 0; i < (int) this->tags.size(); i++) {
        retVal.append(this->tags.at(i));
        if (i + 1 != (int) this->tags.size())
            retVal.append(", ");
    }
    retVal.append("]");
    return retVal;

}

Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags): Watchable(id,length,tags), name(name) {}

//Rule of 3
Movie::Movie(const Movie &other) : Watchable(other), name(other.name){}

Movie& Movie::operator=(const Movie &other) {
    if(this!= &other) {
        this->name = other.name;
        this->setLength(other.getLength());
        this->setTags(other.getTags());
    }
    return *this;
}

Movie::~Movie() {}
//

Watchable* Movie::copyMe() const {
    Movie* m = new Movie(this->getId(),this->getName(),this->getLength(),this->getTags());
    return m;
}

std::string Movie::stringForWatching() const {
    return this->getName();
}

Watchable* Movie::getNextWatchable(Session &) const {
    return nullptr;
}

std::string Movie::toString() const {
    return to_string(this->getId()) + ". " + this->name + " " + to_string(this->getLength()) + " minutes " + this->getTagsStr();
}

std::string Movie::toStringWithoutID() const {
    return (this->name + " " + to_string(this->getLength()) + " minutes " + this->getTagsStr());
}


Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags):Watchable(id,length,tags), seriesName(seriesName), season(season), episode(episode), nextEpisodeId(id+1) {
}

// Overload Ctor
Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags, int nextEpisodeID):Watchable(id,length,tags), seriesName(seriesName), season(season), episode(episode), nextEpisodeId(nextEpisodeID) {
}



//Rule of 3
Episode::~Episode() {}

Episode:: Episode(const Episode& other): Watchable(other), seriesName(other.seriesName), season(other.season), episode(other.episode), nextEpisodeId(other.nextEpisodeId) {}

Episode& Episode::operator=(const Episode &other) {
    if(this != &other) {
        this->seriesName = other.seriesName;
        this->setLength(other.getLength());
        this->season = other.season;
        this->episode = other.episode;
        this->setTags(other.getTags());
        this->nextEpisodeId = other.nextEpisodeId;
    }
    return (*this);
}
//



Watchable* Episode::copyMe() const {
    Episode* e = new Episode(this->getId(),this->seriesName,this->getLength(),this->season,this->episode,this->getTags(),this->nextEpisodeId);
    return e;
}



Watchable* Episode::getNextWatchable(Session& sess) const {
    if (this->nextEpisodeId == -1) {
        return nullptr;
    } else {
        return sess.getContent().at(this->nextEpisodeId - 1);
    }
}

void Episode::Set_next_Episode_ID(int next) {
    this->nextEpisodeId = next;
}

long Episode::get_Next_Episode_ID() {
    return this->nextEpisodeId;
}

std::string Episode::stringForWatching() const {
    return this->seriesName + " S"+to_string(this->season) + "E"+to_string(this->episode);
}

std::string Episode::toString() const {
    return to_string(this->getId()) + ". " + this->seriesName + " S" + to_string(this->season) + "E" + to_string(this->episode) + " " + to_string(this->getLength())+ " minutes " + this->getTagsStr();
}

std::string Episode::toStringWithoutID() const {
    return (this->seriesName + " S" + to_string(this->season) + "E" + to_string(this->episode) + " " + to_string(this->getLength())+ " minutes " + this->getTagsStr());
}

string Episode::getName() const {return seriesName;}
string Movie::getName() const {return name;}