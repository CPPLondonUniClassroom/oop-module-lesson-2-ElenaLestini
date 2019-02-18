#pragma once

//This is for part 1
class ILogger {
public:
    virtual ILogger& LogInfo(const std::string&) = 0;
    virtual ILogger& LogError(const std::string&) = 0;
    virtual const std::string& GetLastError() const = 0;
    virtual ~ILogger() = default;
};

// This is for Part 2/3
class StringLogger : public ILogger {
    std::ostream& o;
    std::string lastError;
public:
    StringLogger(std::ostream& o) : o{o} {}
    ILogger& LogInfo(const std::string& s) override { o << "INFO: " << s; return *this; }
    ILogger& LogError(const std::string& s) override { o << "ERROR: " << s; lastError = s; return *this; }
    const std::string& GetLastError() const override { return lastError; }
};
