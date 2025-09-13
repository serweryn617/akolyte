#ifndef LIB_LOGGER_LOGGER_H
#define LIB_LOGGER_LOGGER_H

class Logger
{
public:
    Logger();
    void print(const char *format, ...);
};

extern Logger g_logger;

#endif  // LIB_LOGGER_LOGGER_H
