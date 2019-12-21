#ifndef EVENTSOURCEINTERFACE_H
#define EVENTSOURCEINTERFACE_H

#include "eventlistenerinterface.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

class EventSourceInterface
{
public:
    EventSourceInterface();
    static int listeners_count_;
    void RegisterEventListener(EventListenerInterface* new_listener);
    void UnRegisterEventListener(EventListenerInterface* listener);
    void notify(string event,map<string,string> params);

private:
    map<int,EventListenerInterface*> regisered_listeners_;
};

#endif // EVENTSOURCEINTERFACE_H
