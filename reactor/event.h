#ifndef __EVENT__
#define __EVENT__
typedef unsigned int Event;
enum EventMask {
    ReadEvent  = 0x01,
    WriteEvent = 0x02,
    ErrorEvent = 0x04,
    EventMask  = 0xff
};
#endif
