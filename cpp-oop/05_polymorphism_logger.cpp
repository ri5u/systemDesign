#include <iostream>
#include <string>
#include <vector>

class LogAppender{
protected:
    std::string appenderName;
public:
    explicit LogAppender(std::string name) : appenderName(name) {};
    virtual ~LogAppender(){
        std::cout << "[Base Virtual Destructor] ~LogAppender() for " << appenderName << std::endl;
    }

    virtual void append(const std::string& logLevel, const std::string& message) {
       std::cout << "[BASE APPENDER] [ " << logLevel << " ] " << message << std::endl;
    }
};

class ConsoleAppender : public LogAppender {
public:
    explicit ConsoleAppender(std::string name) : LogAppender(name) {};
    ~ConsoleAppender() override{
        std::cout << "[Derived Destructor] ~ConsoleAppender() " << std::endl;
    }
    void append(const std::string& logLevel, const std::string& message) override {
        std::cout << "[CONSOLE :: " << appenderName << "] [ " << logLevel << "] -> " << message << std::endl;
    }
};

class FileAppender : public LogAppender {
private:
    std::string filePath;
public:
    FileAppender(std::string name, std::string path) : LogAppender(name), filePath(path) {};
    ~FileAppender() override {
        std::cout << "[Derived Destructor] ~FileAppender() closing " << filePath << std::endl;
    }

    void append(const std::string& logLevel, const std::string& message) override {
        std::cout << "[FILE :: " << filePath << "] [ " << logLevel << "] -> " << message << std::endl;
    }
};

int main(void){
    std::vector<LogAppender*> appenders;
    appenders.push_back(new ConsoleAppender("StandardOut"));
    appenders.push_back(new FileAppender("DiskLogger", "/var/log/system.log"));
    for(LogAppender* appender : appenders) {
        appender->append("INFO", "Sys Initialized Successfully");
    }

    for(LogAppender* appender : appenders) {
        delete appender;
    }
}
