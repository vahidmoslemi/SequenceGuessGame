#ifndef EVENTLISTENERINTERFACE_H
#define EVENTLISTENERINTERFACE_H

#include <string>
#include <unordered_map>

class EventListenerInterface
{
public:
    EventListenerInterface();
    virtual ~EventListenerInterface();
    virtual void handleEvent(std::string event,std::unordered_map<std::string,std::string> params)=0;
};

#endif // EVENTLISTENERINTERFACE_H
