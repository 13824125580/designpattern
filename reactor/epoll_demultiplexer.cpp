#include <vector>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

#include "epoll_demultiplexer.h"

EpollDemultiplexer::EpollDemultiplexer() : _max_fd(0) {
    _epoll_fd = epoll_create(1024);
}

EpollDemultiplexer::~EpollDemultiplexer() {
    close(_epoll_fd);
}

int EpollDemultiplexer::wait_event(std::map<Handle, EventHandler*>& handlers, int timeout) {
    std::vector<struct epoll_event> events(_max_fd);
    int num = epoll_wait(_epoll_fd, &events[0], _max_fd, timeout);
    if (num < 0) {
        //std::cerr << "WARNING: epoll_wait error " << errno << std::endl;
        return num;
    }

    for (int i = 0; i < num; ++i) {
        Handle handle = events[i].data.fd;
        if ((EPOLLHUP|EPOLLERR) & events[i].events) {
            assert(handlers[handle] != NULL);
            (handlers[handle])->handle_error();
        } else {
            if ((EPOLLIN) & events[i].events) {
                assert(handlers[handle] != NULL);
                (handlers[handle])->handle_read();
            }
            if (EPOLLOUT & events[i].events) {
                (handlers[handle])->handle_write();
            }
        }
    }
    return num;
}

int EpollDemultiplexer::regist(Handle handle, Event evt) {
    struct epoll_event ev;
    ev.data.fd = handle;
    if (evt & ReadEvent) {
        ev.events |= EPOLLIN;
    }
    if (evt & WriteEvent) {
        ev.events |= EPOLLOUT;
    }
    ev.events |= EPOLLET;

    if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, handle, &ev) != 0) { 
        if (errno == ENOENT) {
            if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, handle, &ev) != 0) {
                std::cerr << "epoll_ctl add error " << errno << std::endl;
                return -errno;
            }
            ++_max_fd;
        } else {
            ++_max_fd;
        }
    }
    return 0;
}

int EpollDemultiplexer::remove(Handle handle) {
    struct epoll_event ev;
    if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, handle, &ev) != 0) {
        std::cerr << "epoll_ctl del error" << errno << std::endl;
        return -errno;
    }
    --_max_fd;
    return 0;
}
