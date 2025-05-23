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

#include <fstream>
#include <slfmt/LoggerBase.h>

namespace slfmt {
    /**
     * @brief File logger for slfmt.
     */
    class FileLogger : public LoggerBase {
    public:
        /**
         * @brief Constructs a new logger for the specified class and file.
         *
         * @param clazz The class to create a logger for.
         * @param file The file to log to.
         */
        FileLogger(const std::string_view &clazz, const std::string_view &file)
            : LoggerBase(clazz), m_stream(file.data(), std::ios::out | std::ios::app) {}

        ~FileLogger() override {
            m_stream.flush(); // Flush the stream before closing the file.
            m_stream.close();
        }

    private:
        /**
         * @brief The output stream for the file to log to.
         *
         * @note the mode <b>std::ios::app (seek to end before each write)</b> allows having
         * multiple instances of loggers, writing to the same file <b>without</b> overwriting each other.
         */
        std::ofstream m_stream;

        void Trace_Internal(std::string_view msg) override {
            WriteAndFlushStream(FORMAT_MAPPED_PARAMS_FOR_LEVEL(TRACE_LEVEL_STRING));
        }

        void Debug_Internal(std::string_view msg) override {
            WriteAndFlushStream(FORMAT_MAPPED_PARAMS_FOR_LEVEL(DEBUG_LEVEL_STRING));
        }

        void Info_Internal(std::string_view msg) override {
            WriteAndFlushStream(FORMAT_MAPPED_PARAMS_FOR_LEVEL(INFO_LEVEL_STRING));
        }

        void Warn_Internal(std::string_view msg) override {
            WriteAndFlushStream(FORMAT_MAPPED_PARAMS_FOR_LEVEL(WARN_LEVEL_STRING));
        }

        void Error_Internal(std::string_view msg) override {
            WriteAndFlushStream(FORMAT_MAPPED_PARAMS_FOR_LEVEL(ERROR_LEVEL_STRING));
        }

        void Fatal_Internal(std::string_view msg) override {
            WriteAndFlushStream(FORMAT_MAPPED_PARAMS_FOR_LEVEL(FATAL_LEVEL_STRING));
        }

        /**
         * @brief Writes the specified message to the file and flushes the stream.
         *
         * @note When flushing the stream, the message is written to the file immediately. So, if the program
         * crashes, the message will be written to the file before the crash.
         *
         * @param format_map The format map to write.
         */
        void WriteAndFlushStream(const std::unordered_map<std::string_view, std::string_view> &format_map) {
            const auto msg = LogFormat::Get().Format(format_map);
            m_stream.write(msg.data(), static_cast<std::streamsize>(msg.size())).flush();
        }
    };
} // namespace slfmt

#endif // SLFMT_FILE_LOGGER_H
