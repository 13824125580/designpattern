#include "reactor_impl.h"
#include <new>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include "epoll_demultiplexer.h"

ReactorImpl::ReactorImpl() {
    _demultiplexer = new (std::nothrow)EpollDemultiplexer();
    assert(_demultiplexer != NULL);
}

ReactorImpl::~ReactorImpl() {
    std::map<Handle, EventHandler*>::iterator iter = _handlers.begin();
    for(; iter != _handlers.end(); ++iter) {
        delete iter->second;
    }

    if (_demultiplexer != NULL) {
        delete _demultiplexer;
    }
}

int ReactorImpl::regist(EventHandler* handler, Event evt) {
    int handle = handler->get_handle();
    if (_handlers.find(handle) == _handlers.end()) {
        _handlers.insert(std::make_pair(handle, handler));
    }
    return _demultiplexer->regist(handle, evt);
}

void ReactorImpl::remove(EventHandler* handler) {
    int handle = handler->get_handle();
    // not check?
    _demultiplexer->remove(handle);

    std::map<Handle, EventHandler*>::iterator iter = _handlers.find(handle);
    delete iter->second;
    _handlers.erase(iter);
}

void ReactorImpl::dispatch(int timeout) {
    _demultiplexer->wait_event(_handlers, timeout);
}
