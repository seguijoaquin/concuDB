#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <time.h>
#include <unistd.h>


class Logger {

private:

    static Logger* logger;
    std::fstream ioFile;
    Logger();
    std::string getTime();

public:
    static Logger* getInstance();
    void debug(std::string message);
    void info(std::string message);
    void warn(std::string message);
    void error(std::string message);
    void insert(std::string key, std::string value, int param);
    void insert(std::string key, std::string value);
    virtual ~Logger();

};

#endif //LOGGER_H
