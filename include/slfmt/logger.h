/*
 * slfmt - A simple logging library for C++
 *
 * logger.h - Logger class for slfmt
 *
 * Copyright (c) 2023 Samuel Castrillo Domínguez
 * All rights reserved.
 *
 * For more information, please see the LICENSE file.
 */

#ifndef SLFMT_LOGGER_H
#define SLFMT_LOGGER_H

#include <cxxabi.h>
#include <fmt/format.h>
#include <memory>
#include <string>

#include "color.h"
#include "fmt/format.h"
#include "level.h"

#define SLFMT_LOGGER(name, clazz) static inline const auto name = slfmt::Logger::GetLogger<clazz>()

static const inline std::string SLFMT_LOG_FORMAT = "[{} ({})] {}\n";

namespace slfmt {
    class Logger {
    private:
        /**
         * @brief Class name for the logger.
         */
        std::string clazz_;

        /**
         * @brief Constructs a new logger for the specified class.
         * @param clazz The class to create a logger for.
         */
        explicit Logger(std::string_view clazz) : clazz_(clazz) {}

        /**
         * @brief Logs a message at the specified level.
         *
         * @param level The level to log at.
         * @param msg The message to log.
         */
        void Log_internal(const slfmt::Level &level, std::string_view msg) const {
            if (level == slfmt::Level::TRACE) {
                Trace(msg);
            } else if (level == slfmt::Level::DEBUG) {
                Debug(msg);
            } else if (level == slfmt::Level::INFO) {
                Info(msg);
            } else if (level == slfmt::Level::WARN) {
                Warn(msg);
            } else if (level == slfmt::Level::ERROR) {
                Error(msg);
            } else if (level == slfmt::Level::FATAL) {
                Fatal(msg);
            }
        }

    public:
        Logger(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger &operator=(Logger &&) = delete;
        ~Logger() = default;

        /**
         * @brief Creates a new logger for the specified class.
         *
         * @tparam C The class to create a logger for.
         * @return A new logger.
         */
        template<typename C>
        static std::unique_ptr<Logger> GetLogger() {
            const std::string &class_name = abi::__cxa_demangle(typeid(C).name(), nullptr, nullptr, nullptr);
            return std::unique_ptr<Logger>(new Logger(class_name));
        };

        /**
         * @brief Logs a message at the specified level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param level The level to log at.
         * @param msg The message to log.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Log(const slfmt::Level &level, std::string_view msg, Args&&... args) const {
            Log_internal(level, (std::string) fmt::vformat(msg, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the TRACE level.
         *
         * @param msg The message to log.
         */
        void Trace(std::string_view msg) const {
            fmt::print(slfmt::color::TRACE_COLOR, SLFMT_LOG_FORMAT, "TRACE", clazz_, msg);
        }

        /**
         * @brief Logs a message at the TRACE level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Trace(std::string_view format, Args&&... args) const {
            Trace((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the DEBUG level.
         *
         * @param msg The message to log.
         */
        void Debug(std::string_view msg) const {
            fmt::print(slfmt::color::DEBUG_COLOR, SLFMT_LOG_FORMAT, "DEBUG", clazz_, msg);
        }

        /**
         * @brief Logs a message at the DEBUG level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Debug(std::string_view format, Args&&... args) const {
            Debug((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the INFO level.
         *
         * @param msg The message to log.
         */
        void Info(std::string_view msg) const {
            fmt::print(slfmt::color::INFO_COLOR, SLFMT_LOG_FORMAT, "INFO", clazz_, msg);
        }

        /**
         * @brief Logs a message at the INFO level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Info(std::string_view format, Args&&... args) const {
            Info((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the WARN level.
         *
         * @param msg The message to log.
         */
        void Warn(std::string_view msg) const {
            fmt::print(slfmt::color::WARN_COLOR, SLFMT_LOG_FORMAT, "WARN", clazz_, msg);
        }

        /**
         * @brief Logs a message at the WARN level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Warn(std::string_view format, Args&&... args) const {
            Warn((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the ERROR level.
         *
         * @param msg The message to log.
         */
        void Error(std::string_view msg) const {
            fmt::print(slfmt::color::ERROR_COLOR, SLFMT_LOG_FORMAT, "ERROR", clazz_, msg);
        }

        /**
         * @brief Logs a message at the ERROR level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Error(std::string_view format, Args&&... args) const {
            Error((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the FATAL level.
         *
         * @param msg The message to log.
         */
        void Fatal(std::string_view msg) const {
            fmt::print(slfmt::color::FATAL_COLOR, SLFMT_LOG_FORMAT, "FATAL", clazz_, msg);
        }

        /**
         * @brief Logs a message at the FATAL level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Fatal(std::string_view format, Args&&... args) const {
            Fatal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }
    };
} // namespace slfmt

#endif // SLFMT_LOGGER_H
