/*
* slfmt - A simple logging library for C++
*
* ConsoleLogger.h - Console logger for slfmt
*
* Copyright (c) 2023 Samuel Castrillo Domínguez
* All rights reserved.
*
* For more information, please see the LICENSE file.
*/

#ifndef SLFMT_CONSOLE_LOGGER_H
#define SLFMT_CONSOLE_LOGGER_H

#include <slfmt/LoggerBase.h>

namespace slfmt {
    class ConsoleLogger : public LoggerBase {
    public:
        explicit ConsoleLogger(const std::string_view &clazz) : LoggerBase(clazz) {}

    private:
        void Trace_Internal(std::string_view msg) override {
            fmt::print(slfmt::color::TRACE_COLOR, SLFMT_LOG_FORMAT, "TRACE", GetClass(), msg);
        }

        void Debug_Internal(std::string_view msg) override {
            fmt::print(slfmt::color::DEBUG_COLOR, SLFMT_LOG_FORMAT, "DEBUG", GetClass(), msg);
        }

        void Info_Internal(std::string_view msg) override {
            fmt::print(slfmt::color::INFO_COLOR, SLFMT_LOG_FORMAT, "INFO", GetClass(), msg);
        }

        void Warn_Internal(std::string_view msg) override {
            fmt::print(slfmt::color::WARN_COLOR, SLFMT_LOG_FORMAT, "WARN", GetClass(), msg);
        }

        void Error_Internal(std::string_view msg) override {
            fmt::print(slfmt::color::ERROR_COLOR, SLFMT_LOG_FORMAT, "ERROR", GetClass(), msg);
        }

        void Fatal_Internal(std::string_view msg) override {
            fmt::print(slfmt::color::FATAL_COLOR, SLFMT_LOG_FORMAT, "FATAL", GetClass(), msg);
        }
    };
} // namespace slfmt

#endif // SLFMT_CONSOLE_LOGGER_H
