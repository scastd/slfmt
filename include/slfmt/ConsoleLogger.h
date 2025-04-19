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
    /**
     * @brief Console logger for slfmt.
     */
    class ConsoleLogger : public LoggerBase {
    public:
        /**
         * @brief Construct a new ConsoleLogger object.
         *
         * @param clazz Class name.
         */
        explicit ConsoleLogger(const std::string_view &clazz) : LoggerBase(clazz) {}

    private:
        void Trace_Internal(const std::string_view msg) override {
            Print(slfmt::color::TRACE_COLOR, FORMAT_MAPPED_PARAMS_FOR_LEVEL(TRACE_LEVEL_STRING));
        }

        void Debug_Internal(const std::string_view msg) override {
            Print(slfmt::color::DEBUG_COLOR, FORMAT_MAPPED_PARAMS_FOR_LEVEL(DEBUG_LEVEL_STRING));
        }

        void Info_Internal(const std::string_view msg) override {
            Print(slfmt::color::INFO_COLOR, FORMAT_MAPPED_PARAMS_FOR_LEVEL(INFO_LEVEL_STRING));
        }

        void Warn_Internal(const std::string_view msg) override {
            Print(slfmt::color::WARN_COLOR, FORMAT_MAPPED_PARAMS_FOR_LEVEL(WARN_LEVEL_STRING));
        }

        void Error_Internal(const std::string_view msg) override {
            Print(slfmt::color::ERROR_COLOR, FORMAT_MAPPED_PARAMS_FOR_LEVEL(ERROR_LEVEL_STRING));
        }

        void Fatal_Internal(const std::string_view msg) override {
            Print(slfmt::color::FATAL_COLOR, FORMAT_MAPPED_PARAMS_FOR_LEVEL(FATAL_LEVEL_STRING));
        }

        static void Print(const fmt::text_style &color,
                          const std::unordered_map<std::string_view, std::string_view> &format) {
            fmt::print(color, fmt::runtime(LogFormat::Get().Format(format)));
        }
    };
} // namespace slfmt

#endif // SLFMT_CONSOLE_LOGGER_H
