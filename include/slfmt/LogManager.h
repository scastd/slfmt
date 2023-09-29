#ifndef SLFMT_LOG_MANAGER_H
#define SLFMT_LOG_MANAGER_H

#include <slfmt/ConsoleLogger.h>
#include <slfmt/LoggerBase.h>

#define SLFMT_CONSOLE_LOGGER(name, clazz) static inline const auto name = slfmt::LogManager::GetConsoleLogger(#clazz)
#define SLFMT_FILE_LOGGER(name, clazz) static inline const auto name = slfmt::LogManager::GetFileLogger(#clazz)
#define SLFMT_FILE_LOGGER_NAME(name, clazz, filename)                                                                  \
    static inline const auto name = slfmt::LogManager::GetFileLogger(#clazz, filename);

static constexpr std::string_view s_defaultLoggerFilename = "app.log";

namespace slfmt {
    class LogManager {
    public:
        LogManager() = delete;
        ~LogManager() = delete;

        static std::unique_ptr<LoggerBase> GetConsoleLogger(const std::string_view &clazz) {
            return std::make_unique<ConsoleLogger>(clazz);
        }

        static std::unique_ptr<LoggerBase> GetFileLogger(const std::string_view &clazz, const std::string_view &file) {
            return std::make_unique<FileLogger>(clazz, file);
        }

        static std::unique_ptr<LoggerBase> GetFileLogger(const std::string_view &clazz) {
            return GetFileLogger(clazz, s_defaultLoggerFilename);
        }
    };
} // namespace slfmt

#endif // SLFMT_LOG_MANAGER_H
