#include "eventsourceinterface.h"

EventSource::EventSource()
{

}

void EventSource::registerEventListener(std::shared_ptr<EventListenerInterface> new_listener)
{
    m_regisered_listeners.push_back(new_listener);

#ifdef DEBUG_ENABLED
    std::cout<<"New Listener Registed. Total count: "<<m_regisered_listeners.size()<<std::endl;
#endif
}

void EventSource::unRegisterEventListener(std::shared_ptr<EventListenerInterface> listener)
{
    //use find_if instead of find because it gets the predicate. o.w error will occure
    auto pos = std::find_if(m_regisered_listeners.begin(),m_regisered_listeners.end(),
                         [&listener](std::weak_ptr<EventListenerInterface> item) -> bool {
                               return listener == item.lock();
                         });
    if(pos!=m_regisered_listeners.end())
    {
        m_regisered_listeners.erase(pos);
    }
}

void EventSource::notify(std::string event, std::map<std::string, std::string> params)
{
    std::for_each(m_regisered_listeners.begin(),m_regisered_listeners.end(),
                  [&event,&params](std::weak_ptr<EventListenerInterface> listener) -> void
                  {
                    //get shared_ptr of type EventListenerInterface
                    auto plistener = listener.lock();
                    if(plistener)
                    {
                        plistener->handleEvent(event,params);
                    }
                  }
    );
}
