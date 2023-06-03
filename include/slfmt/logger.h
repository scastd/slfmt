#ifndef SLFMT_LOGGER_H
#define SLFMT_LOGGER_H

#include <fmt/format.h>

#include <cxxabi.h>
#include <memory>
#include <string>

#include "color.h"
#include "fmt/format.h"

#define CLASS_LOGGER(name, clazz) static inline const auto name = slfmt::Logger::GetLogger<clazz>()

namespace slfmt {
    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    class Logger {
    private:
        std::string clazz_;

        explicit Logger(std::string_view clazz) : clazz_(clazz) {}

        void Log(const slfmt::Level &level, std::string_view msg) const {
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
         * @tparam C The class to create a logger for.
         * @return A new logger.
         */
        template<typename C>
        static std::unique_ptr<Logger> GetLogger() {
            const std::string &class_name = abi::__cxa_demangle(typeid(C).name(), nullptr, nullptr, nullptr);
            return std::unique_ptr<Logger>(new Logger(class_name));
        };

        template<typename... Args>
        void Log(const slfmt::Level &level, std::string_view msg, Args... args) const {
            Log(level, (std::string) fmt::format(msg, args...));
        }

        /*-------------------------*/
        /* TRACE                   */
        /*-------------------------*/

        void Trace(std::string_view msg) const {
            fmt::print(slfmt::color::TRACE_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Trace(std::string_view format, Args... args) const {
            Trace((std::string) fmt::format(format, args...));
        }

        /*-------------------------*/
        /* DEBUG                   */
        /*-------------------------*/

        void Debug(std::string_view msg) const {
            fmt::print(slfmt::color::DEBUG_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Debug(std::string_view format, Args... args) const {
            Debug((std::string) fmt::format(format, args...));
        }

        /*-------------------------*/
        /* INFO                    */
        /*-------------------------*/

        void Info(std::string_view msg) const {
            fmt::print(slfmt::color::INFO_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Info(std::string_view format, Args... args) const {
            Info((std::string) fmt::format(format, args...));
        }

        /*-------------------------*/
        /* WARNING				   */
        /*-------------------------*/

        void Warn(std::string_view msg) const {
            fmt::print(slfmt::color::WARN_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Warn(std::string_view format, Args... args) const {
            Warn((std::string) fmt::format(format, args...));
        }

        /*-------------------------*/
        /* ERROR                   */
        /*-------------------------*/

        void Error(std::string_view msg) const {
            fmt::print(slfmt::color::ERROR_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Error(std::string_view format, Args... args) const {
            Error((std::string) fmt::format(format, args...));
        }

        /*-------------------------*/
        /* FATAL                   */
        /*-------------------------*/

        void Fatal(std::string_view msg) const {
            fmt::print(slfmt::color::FATAL_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Fatal(std::string_view format, Args... args) const {
            Fatal((std::string) fmt::format(format, args...));
        }
    };
} // namespace slfmt

#endif // SLFMT_LOGGER_H
