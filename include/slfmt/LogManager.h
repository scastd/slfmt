#ifndef SLFMT_LOG_MANAGER_H
#define SLFMT_LOG_MANAGER_H

#include <slfmt/ConsoleLogger.h>
#include <slfmt/LoggerBase.h>

#define SLFMT_CONSOLE_LOGGER(name, clazz) static inline const auto name = slfmt::LogManager::GetConsoleLogger(#clazz)
#define SLFMT_FILE_LOGGER(name, clazz)                                                                                 \
    static inline const auto name = slfmt::LogManager::GetFileLogger(#clazz, "log_test.log")

namespace slfmt {
    class LogManager {
    public:
        static std::unique_ptr<LoggerBase> GetConsoleLogger(const std::string_view &clazz) {
            return std::make_unique<ConsoleLogger>(clazz);
        }

        static std::unique_ptr<LoggerBase> GetFileLogger(const std::string_view &clazz, const std::string_view &file) {
            return std::make_unique<FileLogger>(clazz, file);
        }
    };
} // namespace slfmt

#endif // SLFMT_LOG_MANAGER_H
