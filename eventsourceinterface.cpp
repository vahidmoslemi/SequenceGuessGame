#include "eventsourceinterface.h"

EventSourceInterface::EventSourceInterface()
{

}

void EventSourceInterface::registerEventListener(std::shared_ptr<EventListenerInterface> new_listener)
{
//    std::lock_guard<std::mutex> lock(shared_buffer_lock);
    m_regisered_listeners.push_back(new_listener);

#ifdef DEBUG_ENABLED
    std::cout<<"New Listener Registed. Total count: "<<m_regisered_listeners.size()<<std::endl;
#endif
}

void EventSourceInterface::unRegisterEventListener(std::shared_ptr<EventListenerInterface> listener)
{
//    std::lock_guard<std::mutex> lock(shared_buffer_lock);
    //use find_if instead of find because it gets the predicate. o.w error will occure
    auto pos = std::find_if(m_regisered_listeners.begin(),m_regisered_listeners.end(),
                         [&listener](std::weak_ptr<EventListenerInterface> item){
                               return listener == item.lock();
                         });
    if(pos!=m_regisered_listeners.end())
    {
        m_regisered_listeners.erase(pos);
    }
}

void EventSourceInterface::notify(std::string event, std::map<std::string, std::string> params)
{
    //IMPORTANT
    //-----------------------------------------------------------------------------------------------------------------
    //if you uncomment the line bellow, application will fell into a deadlock when you guess the right sequence
    //because all the core is running in a single thread (we have another thread for UI, thanks to Qt)
    //Then When we are in notify, cpu is fully dedicated to this method untile it completes,
    //inside handleEvent method of uiHandler, we have run again notify to let GameCore to generate a new sequence to
    //guess, and because of the line bellow, it will wait for the lock to be release.
    //BUT bad point is that the first notify call will not finish!!! So two method call will wait for eachother to finish
    //forever!!!

//    std::lock_guard<std::mutex> lock(shared_buffer_lock);

    std::for_each(m_regisered_listeners.begin(),m_regisered_listeners.end(),
                  [event,params](std::weak_ptr<EventListenerInterface> listener){
            std::shared_ptr<EventListenerInterface> plistener = listener.lock();
            if(plistener)
            {
                plistener->handleEvent(event,params);
            }
        }
    );
}
