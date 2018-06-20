#ifndef __reactor_impl__
#define __reactor_impl__
#include <map>
#include "event.h"
#include "event_handler.h"
#include "event_demultiplexer.h"

class ReactorImpl {
public:
    ReactorImpl();
    ~ReactorImpl();
    int regist(EventHandler* handler, Event evt);
    void remove(EventHandler* handler);
    void dispatch(int timeout = 0);

private:
    EventDemultiplexer* _demultiplexer;
    std::map<Handle, EventHandler*> _handlers;
};
#endif
