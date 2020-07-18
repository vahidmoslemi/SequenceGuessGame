#ifndef EVENTSOURCE_H
#define EVENTSOURCE_H

#include<algorithm>
#include "eventlistenerinterface.h"
#include "common.h"

class EventSource
{
public:
    EventSource();
    void registerEventListener(std::shared_ptr<EventListenerInterface> new_listener);
    void unRegisterEventListener(std::shared_ptr<EventListenerInterface> listener);
    void notify(std::string event,std::map<std::string,std::string> params);

private:
    std::vector<std::weak_ptr<EventListenerInterface>> m_regisered_listeners;
};

#endif // EVENTSOURCEINTERFACE_H
