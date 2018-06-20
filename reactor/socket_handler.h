#ifndef __socket_handler__
#define __socket_handler__
#include "event_handler.h"
#include "event.h"

class SocketHandler : public EventHandler {
public:
    SocketHandler(Handle fd);
    virtual ~SocketHandler();
    virtual Handle get_handle() const {
        return _socket_fd;
    }
    virtual void handle_read();
    virtual void handle_write();
    virtual void handle_error();
private:
    Handle _socket_fd;
    char* _buf;
    static const int MAX_SIZE = 1024;
};
#endif
