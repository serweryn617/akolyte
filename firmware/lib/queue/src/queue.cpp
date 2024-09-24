#include "queue/queue.hpp"

namespace lib::queue {

queue_t Queue::queue;

void Queue::initialize()
{
    queue_init(&queue, sizeof(uint32_t), 64);
}

bool Queue::add(Command command)
{
    return queue_try_add(&queue, &command);  // TODO: Static cast?
}

Command Queue::get()
{
    Command command = Command::none;
    queue_try_remove(&queue, &command);
    return command;
}

}  // namespace lib::queue
