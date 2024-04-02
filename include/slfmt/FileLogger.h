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
#include <filesystem>

namespace slfmt {
    /**
     * @brief File logger for slfmt.
     */
    class FileLogger : public LoggerBase {
    public:
        static const size_t DEFAULT_FILE_SIZE = 1024 * 1024 * 5; // 5 MB
        static const size_t MIN_FILE_SIZE = 1024 * 1024; // 1 MB

        /**
         * @brief Constructs a new logger for the specified class and file.
         *
         * @param clazz The class to create a logger for.
         * @param file The file to log to.
         * @param fileSize The maximum size (in bytes) of the log file before rolling it over.
         */
        FileLogger(const std::string_view &clazz, const std::string_view &file,
                   const size_t fileSize = DEFAULT_FILE_SIZE)
                : LoggerBase(clazz), m_stream(file.data(), std::ios::out | std::ios::app), m_file(file.data()),
                  fileSizeLimit(fileSize) {
            if (fileSize < MIN_FILE_SIZE) {
                // Warn the user that the specified size is too small. This could lead to a lot of file rollovers
                // and/or data loss.
                Warn("Specified file size is too small. Using the minimum allowed size ({} MB).",
                     MIN_FILE_SIZE / 1024 / 1024);

                fileSizeLimit = MIN_FILE_SIZE;
            }
        }

        ~FileLogger() override {
            m_stream.flush(); // Flush the stream before closing the file.
            m_stream.close();
        }

    private:
        /**
         * @brief The output stream for the file to log to.
         *
         * @note the mode <b>std::ios::app <i>(seeks to end before each write)</i></b> allows having
         * multiple instances of loggers, writing to the same file <b>without</b> overwriting each other.
         */
        std::ofstream m_stream;

        /**
         * @brief The file to log to.
         */
        const std::string_view m_file;

        /**
         * @brief The maximum size (in bytes) of the log file before rolling it over.
         */
        size_t fileSizeLimit;

        /**
         * @brief The current size of the log file.
         */
        std::streamsize m_currentFileSize = 0;

        void Trace_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(TRACE_LEVEL_STRING)));
        }

        void Debug_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(DEBUG_LEVEL_STRING)));
        }

        void Info_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(INFO_LEVEL_STRING)));
        }

        void Warn_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(WARN_LEVEL_STRING)));
        }

        void Error_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(ERROR_LEVEL_STRING)));
        }

        void Fatal_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(FATAL_LEVEL_STRING)));
        }

        /**
         * @brief Writes the specified message to the file and flushes the stream.
         *
         * @note When flushing the stream, the message is written to the file immediately. So, if the program
         * crashes, the message will be written to the file before the crash. In addition, the file is rolled
         * over when the current file size exceeds the specified file size limit.
         *
         * @param msg The message to write.
         */
        void WriteAndFlushStream(std::string_view msg) {
            auto msgSize = (std::streamsize) msg.size();
            m_stream.write(msg.data(), msgSize).flush();

            m_currentFileSize += msgSize;

            if (m_currentFileSize >= fileSizeLimit) {
                m_stream.close();

                // Backup the current log file.
                MoveFile(m_file, BackupFileName(m_file));

                // Open the new log file.
                m_stream.open(m_file.data(), std::ios::out | std::ios::app);

                if (!m_stream.is_open()) {
                    throw std::runtime_error("Failed to open log file.");
                }

                m_currentFileSize = 0;
            }
        }

        /**
         * @brief Moves the specified source file to the specified destination file.
         *
         * @param srcFile The source file to move.
         * @param dstFile The destination file to move to.
         */
        static void MoveFile(const std::string_view &srcFile, const std::string_view &dstFile) {
            std::filesystem::path srcPath(srcFile.data());
            std::filesystem::path dstPath(dstFile.data());

            if (!std::filesystem::exists(srcPath)) {
                throw std::runtime_error("Source file does not exist.");
            }

            if (std::filesystem::exists(dstPath)) {
                std::filesystem::remove(dstPath);
            }

            std::filesystem::rename(srcPath, dstPath);
        }

        /**
         * @brief Generates a backup file name for the specified file.
         *
         * @param file The file to generate a backup file name for.
         *
         * @return The backup file name.
         */
        static std::string BackupFileName(const std::string_view &file) {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            struct tm tm{};
            localtime_r(&time, &tm);

            return fmt::format("{}_{:04d}-{:02d}-{:02d}_{:02d}-{:02d}-{:02d}.log",
                               file, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
    };
} // namespace slfmt

#endif // SLFMT_FILE_LOGGER_H
