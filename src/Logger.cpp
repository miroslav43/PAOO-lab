#include "Logger.hpp"
#include <iomanip>
#include <sstream>

Logger *Logger::instance = nullptr;

Logger::Logger() : consoleOutput(true), fileOutput(true)
{
    logFile.open("startup_accelerator.log", std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "Warning: Could not open log file" << std::endl;
        fileOutput = false;
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile << "\n=== Logger shutdown at " << getCurrentTime() << " ===\n"
                << std::endl;
        logFile.close();
    }
}

Logger &Logger::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Logger();
        instance->log("=== Logger initialized ===");
    }
    return *instance;
}

std::string Logger::getCurrentTime() const
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << ltm->tm_hour << ":"
        << std::setw(2) << ltm->tm_min << ":"
        << std::setw(2) << ltm->tm_sec;

    return oss.str();
}

void Logger::log(const std::string &message)
{
    std::string output = "[" + getCurrentTime() + "] " + message;

    if (consoleOutput)
    {
        std::cout << output << std::endl;
    }

    if (fileOutput && logFile.is_open())
    {
        logFile << output << std::endl;
        logFile.flush();
    }
}

void Logger::logConstructor(const std::string &className, const std::string &constructorType, const std::string &objectInfo)
{
    std::string message = "[" + className + "] " + constructorType + " Constructor called";
    if (!objectInfo.empty())
    {
        message += " for: " + objectInfo;
    }
    log(message);
}

void Logger::logDestructor(const std::string &className, const std::string &objectInfo)
{
    std::string message = "[" + className + "] Destructor called";
    if (!objectInfo.empty())
    {
        message += " for: " + objectInfo;
    }
    log(message);
}

void Logger::logOperation(const std::string &operation, const std::string &details)
{
    std::string message = "[OPERATION] " + operation;
    if (!details.empty())
    {
        message += " - " + details;
    }
    log(message);
}

void Logger::logSeparator(const std::string &title)
{
    std::string separator = "\n========================================";

    if (consoleOutput)
    {
        std::cout << separator << std::endl;
        std::cout << title << std::endl;
        std::cout << separator << std::endl;
    }

    if (fileOutput && logFile.is_open())
    {
        logFile << separator << std::endl;
        logFile << title << std::endl;
        logFile << separator << std::endl;
        logFile.flush();
    }
}

void Logger::logInfo(const std::string &message)
{
    log("[INFO] " + message);
}

void Logger::logWarning(const std::string &message)
{
    log("[WARNING] " + message);
}

void Logger::setConsoleOutput(bool enabled)
{
    consoleOutput = enabled;
}

void Logger::setFileOutput(bool enabled)
{
    fileOutput = enabled;
}

void Logger::enableAll()
{
    consoleOutput = true;
    fileOutput = true;
}

void Logger::disableFileLogging()
{
    fileOutput = false;
    if (logFile.is_open())
    {
        logFile.close();
    }
}
