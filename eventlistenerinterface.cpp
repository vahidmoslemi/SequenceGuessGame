#include "eventlistenerinterface.h"


EventListenerInterface::EventListenerInterface()
{
    listener_id_ = 0;
}

EventListenerInterface::~EventListenerInterface()
{
    //Nothing for now
}

int EventListenerInterface::GetListenerId(){
    return listener_id_;
}



