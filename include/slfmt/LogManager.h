/*
* slfmt - A simple logging library for C++
*
* LogManager.h - Log manager for slfmt
*
* Copyright (c) 2023 Samuel Castrillo Domínguez
* All rights reserved.
*
* For more information, please see the LICENSE file.
*/

#ifndef SLFMT_LOG_MANAGER_H
#define SLFMT_LOG_MANAGER_H

#include <slfmt/CombinedLogger.h>
#include <slfmt/ConsoleLogger.h>
#include <slfmt/LoggerBase.h>
#include <slfmt/RollingFileLogger.h>

#define SLFMT_CONSOLE_LOGGER(clazz) slfmt::LogManager::GetConsoleLogger(#clazz)
#define SLFMT_FILE_LOGGER(clazz) slfmt::LogManager::GetFileLogger(#clazz)
#define SLFMT_FILE_LOGGER_NAME(clazz, filename) slfmt::LogManager::GetFileLogger(#clazz, filename)
#define SLFMT_ROLLING_FILE_LOGGER_NAME(clazz, filename, fileSize)                                                      \
    slfmt::LogManager::GetRollingFileLogger(#clazz, filename, fileSize)

#define SLFMT_CONSOLE_LOGGER_FIELD(name, clazz) static inline const auto name = SLFMT_CONSOLE_LOGGER(clazz)
#define SLFMT_FILE_LOGGER_FIELD(name, clazz) static inline const auto name = SLFMT_FILE_LOGGER(clazz)
#define SLFMT_FILE_LOGGER_NAME_FIELD(name, clazz, filename)                                                            \
    static inline const auto name = SLFMT_FILE_LOGGER_NAME(clazz, filename)
#define SLFMT_ROLLING_FILE_LOGGER_NAME_FIELD(name, clazz, filename, fileSize)                                          \
    static inline const auto name = SLFMT_ROLLING_FILE_LOGGER_NAME(clazz, filename, fileSize)
#define SLFMT_COMBINED_LOGGER_FIELD(name, clazz, ...)                                                                  \
    static inline const auto name = slfmt::LogManager::GetCombinedLogger(#clazz, __VA_ARGS__)

#define SLFMT_FILE_CONSOLE_COMBINED_LOGGER_FIELDS(name, clazz)                                                         \
    SLFMT_COMBINED_LOGGER_FIELD(name, clazz, SLFMT_FILE_LOGGER(clazz), SLFMT_CONSOLE_LOGGER(clazz))

static constexpr std::string_view s_defaultLoggerFilename = "app.log";

namespace slfmt {
    class LogManager {
    public:
        LogManager() = delete;
        ~LogManager() = delete;

        static std::unique_ptr<LoggerBase> GetLogger(const std::string_view &clazz) {
            return GetConsoleLogger(clazz);
        }

        static std::unique_ptr<LoggerBase> GetConsoleLogger(const std::string_view &clazz) {
            return std::make_unique<ConsoleLogger>(clazz);
        }

        static std::unique_ptr<LoggerBase> GetFileLogger(const std::string_view &clazz,
                                                         const std::string_view &file = s_defaultLoggerFilename) {
            return std::make_unique<FileLogger>(clazz, file);
        }

        static std::unique_ptr<LoggerBase> GetRollingFileLogger(const std::string_view &clazz,
                                                                const std::string_view &file, const size_t fileSize) {
            return std::make_unique<RollingFileLogger>(clazz, file, fileSize);
        }

        template<typename... Loggers>
        static std::unique_ptr<LoggerBase> GetCombinedLogger(const std::string_view &clazz, Loggers &&...loggers) {
            std::vector<std::unique_ptr<LoggerBase>> combinedLoggers;

            // Some magic to convert the variadic arguments to a vector of unique_ptr<LoggerBase>
            combinedLoggers.reserve(sizeof...(loggers));
            (combinedLoggers.push_back(std::forward<Loggers>(loggers)), ...);

            return std::make_unique<CombinedLogger>(clazz, std::move(combinedLoggers));
        }
    };
} // namespace slfmt

#endif // SLFMT_LOG_MANAGER_H
