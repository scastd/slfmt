/*
 * slfmt - A simple logging library for C++
 *
 * LoggerBase.h - Logger interface for slfmt
 *
 * Copyright (c) 2023 Samuel Castrillo Domínguez
 * All rights reserved.
 *
 * For more information, please see the LICENSE file.
 */

#ifndef SLFMT_LOGGER_BASE_H
#define SLFMT_LOGGER_BASE_H

#include <fmt/format.h>
#include <memory>
#include <string>

#include "Color.h"
#include "fmt/format.h"
#include "Level.h"

static const std::string SLFMT_LOG_FORMAT = "[{} ({})] {}\n";
static const char *const TRACE_LEVEL_STRING = "TRACE";
static const char *const DEBUG_LEVEL_STRING = "DEBUG";
static const char *const INFO_LEVEL_STRING = "INFO";
static const char *const WARN_LEVEL_STRING = "WARN";
static const char *const ERROR_LEVEL_STRING = "ERROR";
static const char *const FATAL_LEVEL_STRING = "FATAL";

namespace slfmt {
    class LoggerBase {
    private:
        /**
         * @brief Class name for the logger.
         */
        const std::string m_class;

        /**
         * @brief Logs a message at the specified level.
         *
         * @param level The level to log at.
         * @param msg The message to log.
         */
        void Log_Internal(const slfmt::Level &level, std::string_view msg) {
            if (level == slfmt::Level::TRACE) {
                Trace_Internal(msg);
            } else if (level == slfmt::Level::DEBUG) {
                Debug_Internal(msg);
            } else if (level == slfmt::Level::INFO) {
                Info_Internal(msg);
            } else if (level == slfmt::Level::WARN) {
                Warn_Internal(msg);
            } else if (level == slfmt::Level::ERROR) {
                Error_Internal(msg);
            } else if (level == slfmt::Level::FATAL) {
                Fatal_Internal(msg);
            }
        }

        /**
         * @brief Logs a message at the TRACE level.
         *
         * @param msg The message to log.
         */
        virtual void Trace_Internal(std::string_view msg) = 0;

        /**
         * @brief Logs a message at the DEBUG level.
         *
         * @param msg The message to log.
         */
        virtual void Debug_Internal(std::string_view msg) = 0;

        /**
         * @brief Logs a message at the INFO level.
         *
         * @param msg The message to log.
         */
        virtual void Info_Internal(std::string_view msg) = 0;

        /**
         * @brief Logs a message at the WARN level.
         *
         * @param msg The message to log.
         */
        virtual void Warn_Internal(std::string_view msg) = 0;

        /**
         * @brief Logs a message at the ERROR level.
         *
         * @param msg The message to log.
         */
        virtual void Error_Internal(std::string_view msg) = 0;

        /**
         * @brief Logs a message at the FATAL level.
         *
         * @param msg The message to log.
         */
        virtual void Fatal_Internal(std::string_view msg) = 0;

    protected:
        /**
         * @brief Constructs a new logger for the specified class.
         *
         * @param clazz The class to create a logger for.
         */
        explicit LoggerBase(std::string_view clazz) : m_class(clazz) {}

        /**
         * @brief Gets the class name for the logger.
         *
         * @return The class name for the logger.
         */
        FMT_NODISCARD std::string_view GetClass() const {
            return m_class;
        }

    public:
        LoggerBase(const LoggerBase &) = delete;
        LoggerBase(LoggerBase &&) = delete;
        LoggerBase &operator=(const LoggerBase &) = delete;
        LoggerBase &operator=(LoggerBase &&) = delete;

        virtual ~LoggerBase() = default;

        /**
         * @brief Logs a message at the specified level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param level The level to log at.
         * @param msg The message to log.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Log(const slfmt::Level &level, std::string_view msg, Args &&...args) {
            Log_Internal(level, (std::string) fmt::vformat(msg, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the TRACE level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Trace(std::string_view format, Args &&...args) {
            Trace_Internal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the DEBUG level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Debug(std::string_view format, Args &&...args) {
            Debug_Internal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the INFO level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Info(std::string_view format, Args &&...args) {
            Info_Internal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the WARN level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Warn(std::string_view format, Args &&...args) {
            Warn_Internal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the ERROR level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Error(std::string_view format, Args &&...args) {
            Error_Internal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }

        /**
         * @brief Logs a message at the FATAL level.
         *
         * @tparam Args The types of the arguments to format the message with.
         * @param format The format string.
         * @param args The arguments to format the message with.
         */
        template<typename... Args>
        void Fatal(std::string_view format, Args &&...args) {
            Fatal_Internal((std::string) fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
        }
    };
} // namespace slfmt

#endif // SLFMT_LOGGER_BASE_H
