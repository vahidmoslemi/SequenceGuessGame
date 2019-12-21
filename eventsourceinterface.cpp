#include "eventsourceinterface.h"

int EventSourceInterface::listeners_count_=0;
EventSourceInterface::EventSourceInterface()
{

}

void EventSourceInterface::RegisterEventListener(EventListenerInterface *new_listener)
{
    ++listeners_count_;
    regisered_listeners_.insert(pair<int,EventListenerInterface*>(listeners_count_,new_listener));
    new_listener->SetListenerId(listeners_count_);

#ifdef DEBUG_ENABLED
    cout<<"New Listener Registed by id: "<<listeners_count_;
#endif
}

void EventSourceInterface::UnRegisterEventListener(EventListenerInterface *listener)
{
        regisered_listeners_.erase(listener->GetListenerId());
#ifdef DEBUG_ENABLED
        cout<<"Listener UnRegisted by id: "<<listener->GetListenerId();
#endif
}


void EventSourceInterface::notify(string event, map<string, string> params)
{
    for(auto&  [listerner_id, listener] : regisered_listeners_)
    {
        listener->HandleEvent(event,params);
    }
}
