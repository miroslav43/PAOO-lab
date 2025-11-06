#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger
{
private:
    static Logger *instance;
    std::ofstream logFile;
    bool consoleOutput;
    bool fileOutput;

    Logger();

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::string getCurrentTime() const;

public:
    ~Logger();

    static Logger &getInstance();

    void log(const std::string &message);
    void logConstructor(const std::string &className, const std::string &constructorType, const std::string &objectInfo);
    void logDestructor(const std::string &className, const std::string &objectInfo);
    void logOperation(const std::string &operation, const std::string &details);
    void logSeparator(const std::string &title);
    void logInfo(const std::string &message);
    void logWarning(const std::string &message);

    void setConsoleOutput(bool enabled);
    void setFileOutput(bool enabled);
    void enableAll();
    void disableFileLogging();
};

#endif // LOGGER_HPP
