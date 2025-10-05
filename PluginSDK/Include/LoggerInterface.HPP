#ifndef STYXTELEGRAMBOTFRAMEWORK_LOGGERINTERFACE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_LOGGERINTERFACE_HPP

class LoggerInterface {
    public:
        virtual ~LoggerInterface() = default;
        virtual void Info(const char* Message) = 0;
        virtual void Warn(const char* Message) = 0;
        virtual void Error(const char* Message) = 0;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_LOGGERINTERFACE_HPP