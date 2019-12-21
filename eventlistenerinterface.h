#ifndef EVENTLISTENERINTERFACE_H
#define EVENTLISTENERINTERFACE_H

#include <string>
#include <map>
using namespace std;

class EventListenerInterface
{
public:
    EventListenerInterface();
    virtual ~EventListenerInterface();
    virtual void HandleEvent(string event,map<string,string> params)=0;
    void SetListenerId(int id){listener_id_ = id;}
    int GetListenerId();
private:
    int listener_id_;
};

#endif // EVENTLISTENERINTERFACE_H
