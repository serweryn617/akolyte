#ifndef LIB_QUEUE_QUEUE_HPP
#define LIB_QUEUE_QUEUE_HPP

#include "pico/stdlib.h"
#include "pico/util/queue.h"

namespace lib::queue {

enum class Command : uint32_t {
    none,
    caps_on,
    caps_off
};

class Queue
{
public:
    Queue() {}
    void initialize();
    bool add(Command command);
    Command get();

private:
    static queue_t queue;
};

}  // namespace lib::queue

#endif  // LIB_QUEUE_QUEUE_HPP