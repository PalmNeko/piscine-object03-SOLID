#pragma once

#include "ILogger.hpp"

#include <ostream>

class LoggerStream : public ILogger
{
    std::ostream &ostream;

public:
    LoggerStream(std::ostream &ostream) : ostream(ostream) {}
    ~LoggerStream() {}
    LoggerStream(const LoggerStream &other) : ostream(other.ostream) {}

private:
    LoggerStream() : ostream(std::cout) {}

public:
    void write(const std::string &message)
    {
        ostream << message;
    }

private:
    LoggerStream &operator=(LoggerStream &)
    {
        return *this;
    }
};
