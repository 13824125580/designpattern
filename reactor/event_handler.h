#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

typedef int Handle;

class EventHandler {
public:
    EventHandler() {}
    virtual ~EventHandler() {}
    virtual Handle get_handle() const = 0;
    virtual void handle_read() = 0;
    virtual void handle_write() = 0;
    virtual void handle_error() = 0;
};
#endif
