// AppLogger.h

#ifndef APP_LOGGER_H
#define APP_LOGGER_H

#include <string>
#include <sstream>
#include <vector>

#include "Poco/Message.h"

// Forward decalrations (instant including h files)
namespace Poco{class Logger;};
class CMyLogger;

// Application logger: class that handles all application logging.
// It is implemented as a singleton
// Singleton is a design pattern that is used to restrict instantiation of a class to one object.
// This is useful when exactly one object is needed to coordinate actions across the system - for example only one logger.
// Sometimes it is generalized to systems that operate more efficiently when only one or a few objects exist.

class CAppLogger
{
private:
        enum ELogger
        {
                ELoggerFile             = 0,
                ELoggerConsole,

                ELoggersCount
        };

        CAppLogger(void);

public:
        ~CAppLogger(void);

        // The one and only application logger is accessible through this method
        static CAppLogger& Instance()
        {
                // This is the instance.
                static CAppLogger instance;
                static bool firstCall = true;
                if (firstCall)
                {
                        firstCall = false;
                        instance.Log("\n\nStarting new log session.");
                }

                // Return a reference to the instance.
                return instance;
        }

        // Write to log a STL string.
        void Log(const std::string& inLogString, Poco::Message::Priority inPriority = Poco::Message::PRIO_INFORMATION);
        // Write to log a STL string stream.
        void Log(const std::ostringstream& inLogString, Poco::Message::Priority inPriority = Poco::Message::PRIO_INFORMATION);

private:
        // Holds pointers to all loggers
        std::vector<Poco::Logger*> mLoggers;
};

#endif // APP_LOGGER_H

