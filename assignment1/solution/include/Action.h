#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

class BaseAction{
public:
    BaseAction();

    virtual ~BaseAction();

    ActionStatus getStatus() const;
    void setStatus (ActionStatus status);
    void setErrorMessage (std::string errorMsg);
    virtual BaseAction* copyMe() const = 0;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;
protected:
    void complete();
    void error(const std::string& string1);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};

class ChangeActiveUser : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};

class DeleteUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};


class DuplicateUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};

class PrintContentList : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};

class PrintWatchHistory : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};


class Watch : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};


class PrintActionsLog : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};

class Exit : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyMe() const;
};
#endif