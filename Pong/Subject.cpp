#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::AddObserver(Observer *observer)
{
    list_observer.push_back(observer);
}

void Subject::RemoveObserver(Observer *observer)
{
    list_observer.remove(observer);
}

void Subject::Notify()
{
    std::list<Observer *>::iterator iterator = list_observer.begin();

    while (iterator != list_observer.end())
    {
        if ((*iterator)->GetHit())
        {
            (*iterator)->Update();
            (*iterator)->SetHit(false);
        }
        ++iterator;
    }
}
