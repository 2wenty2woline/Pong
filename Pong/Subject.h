#pragma once
#include "Observer.h"
#include <list>

class Subject
{
  private:
    std::list<Observer *> list_observer;

  public:
    Subject();
    virtual ~Subject();

    void AddObserver(Observer *observer);
    void RemoveObserver(Observer *observer);
    void Notify();
};
