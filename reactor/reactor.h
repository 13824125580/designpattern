#ifndef __reactor__
#define __reactor__
#include "event_handler.h"
#include "event.h"
#include "reactor_impl.h"

class ReactorImpl; // 为了隐藏具体实现么。。

class Reactor {
public:
    static Reactor& get_instance();
    int regist(EventHandler* handler, Event evt);
    void remove(EventHandler* handler);
    void dispatch(int timeout = 0);

private:
    Reactor();
    ~Reactor();
    Reactor(const Reactor&);
    Reactor& operator=(const Reactor&);

private:
    ReactorImpl* _reactor_impl;
    static Reactor reactor;
};
#endif
