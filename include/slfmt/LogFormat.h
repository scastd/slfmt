#ifndef SLFMT_LOG_FORMAT_H
#define SLFMT_LOG_FORMAT_H

#include <chrono>
#include <fmt/format.h>
#include <functional>
#include <iomanip>
#include <string>
#include <thread>
#include <vector>

namespace slfmt {
    class LogFormat {
    public:
        /**
         * @brief Default log format.
         *
         * @details The default log format is as follows:
         * <ol>
         *  <li>Timestamp: composed of the date and time in the format `YYYY-MM-DD HH:MM:SS,mmm`.</li>
         *  <li>Level: the level of the log.</li>
         *  <li>Class: the class that logged the message.</li>
         *  <li>Thread: the thread id.</li>
         *  <li>Message: the message to log.</li>
         * </ol>
         */
        static const LogFormat DEFAULT;

        /**
         * @brief Formats the log message with the specified replacements.
         *
         * @param replaces Replacements to use.
         *
         * @return The formatted log message.
         */
        FMT_NODISCARD std::string Format(const std::unordered_map<std::string_view, std::string_view> &replaces) const {
            std::string formatted = m_format;

            for (const auto &function: m_functions) {
                formatted.replace(formatted.find("{}"), 2, function());
            }

            for (const auto &[key, value]: replaces) {
                formatted.replace(formatted.find(key), key.size(), value);
            }

            return formatted;
        }

        /**
         * @brief Builder for the log format.
         */
        class Builder {
        public:
            Builder() = default;

            Builder &Timestamp(const std::string &leftDelimiter = "", const std::string &rightDelimiter = "") {
                m_formats.push_back(Delimit("{}", leftDelimiter, rightDelimiter));
                m_functions.emplace_back(GetTimestampString);
                return *this;
            }

            Builder &Level(const std::string &leftDelimiter = "", const std::string &rightDelimiter = "") {
                m_formats.push_back(Delimit("{}", leftDelimiter, rightDelimiter));
                m_functions.emplace_back([]() {
                    return "{L}";
                });
                return *this;
            }

            Builder &Class(const std::string &leftDelimiter = "(", const std::string &rightDelimiter = ")") {
                m_formats.push_back(Delimit("{}", leftDelimiter, rightDelimiter));
                m_functions.emplace_back([]() {
                    return "{C}";
                });
                return *this;
            }

            Builder &ThreadId(const std::string &leftDelimiter = "[Thread-", const std::string &rightDelimiter = "]") {
                m_formats.push_back(Delimit("{}", leftDelimiter, rightDelimiter));
                m_functions.emplace_back(GetThreadIdString);
                return *this;
            }

            Builder &Message(const std::string &leftDelimiter = "", const std::string &rightDelimiter = "") {
                m_formats.push_back(Delimit("{}", leftDelimiter, rightDelimiter));
                m_functions.emplace_back([]() {
                    return "{M}";
                });
                return *this;
            }

            LogFormat Build() {
                LogFormat logFormat;

                // Each format is separated by a space (except for the last one).
                for (size_t i = 0; i < m_formats.size(); ++i) {
                    logFormat.m_format += m_formats[i];

                    if (i != m_formats.size() - 1) {
                        logFormat.m_format += " ";
                    }
                }

                logFormat.m_format += "\n"; // Add a newline at the end.
                logFormat.m_functions = m_functions;

                return logFormat;
            }

        private:
            std::vector<std::string> m_formats{};
            std::vector<std::function<std::string()>> m_functions{};

            /**
             * @brief Delimits a string with the specified delimiters.
             *
             * @param str String to delimit.
             * @param leftDelimiter Left delimiter to use.
             * @param rightDelimiter Right delimiter to use.
             *
             * @return The delimited string.
             */
            FMT_NODISCARD static std::string Delimit(const std::string &str, const std::string &leftDelimiter,
                                                     const std::string &rightDelimiter) {
                return leftDelimiter + str + rightDelimiter;
            }
        };

    private:
        LogFormat() = default;

        std::string m_format{};
        std::vector<std::function<std::string()>> m_functions{};

        /**
         * @brief Gets the current timestamp as a string.
         *
         * @note The format is as follows: "YYYY-MM-DD HH:MM:SS,mmm".
         *
         * @return The current timestamp as a string.
         */
        static std::string GetTimestampString() {
            auto now = std::chrono::system_clock::now();
            auto nowTime = std::chrono::system_clock::to_time_t(now);
            auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
            struct tm tm = {};

#ifdef _WIN32
            localtime_s(&tm, &nowTime);
#else
            localtime_r(&nowTime, &tm);
#endif

            std::stringstream ss;
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << ',' << std::setfill('0') << std::setw(3) << nowMs.count();
            return ss.str();
        }

        /**
         * @brief Gets the current thread ID as a string.
         *
         * @return The current thread ID as a string.
         */
        static std::string GetThreadIdString() {
            std::stringstream ss;
            ss << std::this_thread::get_id();
            return ss.str();
        }
    };

    const LogFormat LogFormat::DEFAULT = LogFormat::Builder().Timestamp().Level().Class().ThreadId().Message().Build();
} // namespace slfmt

#endif // SLFMT_LOG_FORMAT_H
