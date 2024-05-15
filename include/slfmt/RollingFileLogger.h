#ifndef SLFMT_ROLLING_FILE_LOGGER_H
#define SLFMT_ROLLING_FILE_LOGGER_H

#include <slfmt/LoggerBase.h>

namespace slfmt {
    class RollingFileLogger : public LoggerBase {
    public:
        static const size_t DEFAULT_FILE_SIZE = 1024 * 1024 * 5; // 5 MB
        static const size_t MIN_FILE_SIZE = 1024 * 1024;         // 1 MB

        /**
         * @brief Constructs a new logger for the specified class and file.
         *
         * @param clazz The class to create a logger for.
         * @param file The file to log to.
         * @param fileSize The maximum size (in bytes) of the log file before rolling it over.
         */
        RollingFileLogger(const std::string_view &clazz, const std::string_view &file,
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

            if (!fs::exists(s_backupDir)) {
                fs::create_directory(s_backupDir);
            }

            // If the file exists, get its size, so we can check if it exceeds the specified file size limit when
            // opening it.
            if (fs::exists(file)) {
                m_currentFileSize = fs::file_size(file);

                // If the file size is greater than the specified file size limit, backup the file.
                if (m_currentFileSize >= fileSizeLimit) {
                    CreateBackup();
                    m_currentFileSize = 0;
                }
            }
        }

        ~RollingFileLogger() override {
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
         * @brief The file path to log to.
         */
        const std::string_view m_file;

        /**
         * @brief The maximum size (in bytes) of the log file before rolling it over.
         */
        size_t fileSizeLimit;

        /**
         * @brief The current size of the log file.
         */
        size_t m_currentFileSize = 0;

        /**
         * @brief The directory to store the backup log files.
         */
        static const inline fs::path s_backupDir = fs::path("logs");

        void Trace_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(TRACE_LEVEL_STRING)));
            CheckAndBackupLogFile();
        }

        void Debug_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(DEBUG_LEVEL_STRING)));
            CheckAndBackupLogFile();
        }

        void Info_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(INFO_LEVEL_STRING)));
            CheckAndBackupLogFile();
        }

        void Warn_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(WARN_LEVEL_STRING)));
            CheckAndBackupLogFile();
        }

        void Error_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(ERROR_LEVEL_STRING)));
            CheckAndBackupLogFile();
        }

        void Fatal_Internal(std::string_view msg) override {
            WriteAndFlushStream(fmt::format(fmt::runtime(SLFMT_LOG_FORMAT), LOG_PARAMS_FOR_LEVEL(FATAL_LEVEL_STRING)));
            CheckAndBackupLogFile();
        }

        /**
         * @brief Writes the specified message to the file and flushes the stream.
         *
         * @note When flushing the stream, the message is written to the file immediately. So, if the program
         * crashes, the message will be written to the file <b>before</b> the crash.
         *
         * @param msg The message to write.
         */
        void WriteAndFlushStream(std::string_view msg) {
            auto msgSize = msg.size();
            m_stream.write(msg.data(), (std::streamsize) msgSize).flush();

            m_currentFileSize += msgSize;
        }

        /**
         * @brief Generates a backup file name for the specified file.
         *
         * @param file The file to generate a backup file name for.
         *
         * @return The backup file name.
         */
        static std::string BackupFileName(const fs::path &file) {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);

            struct tm tm {};

#ifdef _WIN32
            localtime_s(&tm, &time);
#else
            localtime_r(&time, &tm);
#endif

            return fmt::format(fmt::runtime("{}_{:04d}-{:02d}-{:02d}_{:02d}-{:02d}-{:02d}"),
                               file.stem().string().c_str(), tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                               tm.tm_min, tm.tm_sec);
        }

        /**
         * @brief Checks if the current log file exceeds the specified file size limit
         * and creates a backup if it does.
         */
        void CheckAndBackupLogFile() {
            if (m_currentFileSize < fileSizeLimit) {
                return;
            }

            m_stream.close();
            CreateBackup();

            // Open the new log file.
            m_stream.open(m_file.data(), std::ios::out | std::ios::app);

            if (!m_stream.is_open()) {
                throw std::runtime_error("Failed to open log file.");
            }

            m_currentFileSize = 0;
        }

        /**
         * Creates a backup of the current log file.
         *
         * @note The backup file is compressed before moving it to the backup directory.
         */
        void CreateBackup() const {
            const auto &backupFilename = BackupFileName(m_file);
            const auto compressedFile = Files::CompressFile(m_file.data(), backupFilename);
            Files::MoveFileToDir(compressedFile, s_backupDir);
            Files::ClearFile(m_file);
        }
    };
} // namespace slfmt

#endif // SLFMT_ROLLING_FILE_LOGGER_H
