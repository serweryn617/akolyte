#pragma once

class Logger
{
private:
    bool is_on = false;

public:
    Logger();
    void set_on(bool on);
    void print(const char *s);
};

