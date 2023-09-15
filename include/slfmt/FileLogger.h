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

#include <slfmt/LoggerBase.h>

namespace slfmt {
    class FileLogger : public LoggerBase {
    private:
        /**
         * @brief The file to log to.
         */
        FILE *m_file;

    public:
        /**
         * @brief Constructs a new logger for the specified class.
         *
         * @param clazz The class to create a logger for.
         * @param file The file to log to.
         */
        explicit FileLogger(const std::string_view &clazz, const std::string_view &file) : LoggerBase(clazz) {
            m_file = fopen(file.data(), "a");
        }

        ~FileLogger() override {
            fflush(m_file); // Flush the file buffer.
            fclose(m_file);
        }

        void Trace(std::string_view msg) const override {
            fmt::print(m_file, SLFMT_LOG_FORMAT, "TRACE", GetClass(), msg);
        }

        void Debug(std::string_view msg) const override {
            fmt::print(m_file, SLFMT_LOG_FORMAT, "DEBUG", GetClass(), msg);
        }

        void Info(std::string_view msg) const override {
            fmt::print(m_file, SLFMT_LOG_FORMAT, "INFO", GetClass(), msg);
        }

        void Warn(std::string_view msg) const override {
            fmt::print(m_file, SLFMT_LOG_FORMAT, "WARN", GetClass(), msg);
        }

        void Error(std::string_view msg) const override {
            fmt::print(m_file, SLFMT_LOG_FORMAT, "ERROR", GetClass(), msg);
        }

        void Fatal(std::string_view msg) const override {
            fmt::print(m_file, SLFMT_LOG_FORMAT, "FATAL", GetClass(), msg);
        }
    };
} // namespace slfmt

#endif // SLFMT_FILE_LOGGER_H
