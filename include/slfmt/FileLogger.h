/*
* slfmt - A simple logging library for C++
*
* FileLogger.h - File logger for slfmt
*
* Copyright (c) 2023 Samuel Castrillo Domínguez
* All rights reserved.
*
* For more information, please see the LICENSE file.
*/

#ifndef SLFMT_FILE_LOGGER_H
#define SLFMT_FILE_LOGGER_H

#include "fmt/os.h"
#include <fmt/ostream.h>
#include <slfmt/LoggerBase.h>

namespace slfmt {
    class FileLogger : public LoggerBase {
    public:
        /**
         * @brief Constructs a new logger for the specified class.
         *
         * @param clazz The class to create a logger for.
         * @param file The file to log to.
         */
        explicit FileLogger(const std::string_view &clazz, const std::string_view &file)
            : LoggerBase(clazz), m_stream(fmt::output_file(file.data())) {}

        ~FileLogger() override {
            m_stream.flush(); // Flush the stream before closing the file.
            m_stream.close();
        }

    private:
        /**
         * @brief The output stream for the file to log to.
         */
        fmt::ostream m_stream;

        void Trace_Internal(std::string_view msg) override {
            m_stream.print(fmt::runtime(SLFMT_LOG_FORMAT), "TRACE", GetClass(), msg);
        }

        void Debug_Internal(std::string_view msg) override {
            m_stream.print(fmt::runtime(SLFMT_LOG_FORMAT), "DEBUG", GetClass(), msg);
        }

        void Info_Internal(std::string_view msg) override {
            m_stream.print(fmt::runtime(SLFMT_LOG_FORMAT), "INFO", GetClass(), msg);
        }

        void Warn_Internal(std::string_view msg) override {
            m_stream.print(fmt::runtime(SLFMT_LOG_FORMAT), "WARN", GetClass(), msg);
        }

        void Error_Internal(std::string_view msg) override {
            m_stream.print(fmt::runtime(SLFMT_LOG_FORMAT), "ERROR", GetClass(), msg);
        }

        void Fatal_Internal(std::string_view msg) override {
            m_stream.print(fmt::runtime(SLFMT_LOG_FORMAT), "FATAL", GetClass(), msg);
        }
    };
} // namespace slfmt

#endif // SLFMT_FILE_LOGGER_H
