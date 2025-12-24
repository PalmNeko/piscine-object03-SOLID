#pragma once

#include "ILogger.hpp"

#include <fstream>

class LoggerFile : public ILogger
{
    std::string filename;

public:
    LoggerFile(const std::string &filename) : filename(filename) {}
    ~LoggerFile() {}
    LoggerFile(const LoggerFile &other) : filename(other.filename) {}

private:
    LoggerFile() {}

public:
    void write(const std::string &message)
    {
        std::ofstream ofs;

        ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
        if (ofs.fail())
            return;
        ofs << message;
    }

public:
    LoggerFile &operator=(LoggerFile &other)
    {
        if (this != &other)
        {
            filename = other.filename;
        }
        return *this;
    }
};
