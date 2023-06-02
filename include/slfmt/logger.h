#ifndef SLFMT_LOGGER_H
#define SLFMT_LOGGER_H

#include <string>
#include <memory>
#include <fmt/format.h>
#include "fmt/format.h"
#include "color.h"

namespace slfmt {
    class Logger {
    private:
        std::string clazz_;

        Logger() = default;

        explicit Logger(std::string_view clazz) : clazz_(clazz) {}

    public:
        Logger(const Logger &) = delete;

        Logger(Logger &&) = delete;

        Logger &operator=(const Logger &) = delete;

        Logger &operator=(Logger &&) = delete;

        ~Logger() = default;

        static std::unique_ptr<Logger> GetLogger(std::string_view c) {
            return std::unique_ptr<Logger>(new Logger(c));
        };

        /*-------------------------*/
        /* TRACE                   */
        /*-------------------------*/

        void Trace(std::string_view msg) const {
            fmt::print(slfmt::color::TRACE_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Trace(std::string_view format, Args... args) const {
            Trace(fmt::format(format, args...));
        }

        void Trace(std::string_view msg, const std::exception &e) const {
            Trace(fmt::format(msg, e.what()));
        }

        /*-------------------------*/
        /* DEBUG                   */
        /*-------------------------*/

        void Debug(std::string_view msg) const {
            fmt::print(slfmt::color::DEBUG_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Debug(std::string_view format, Args... args) const {
            Debug(fmt::format(format, args...));
        }

        void Debug(std::string_view msg, const std::exception &e) const {
            Debug(fmt::format(msg, e.what()));
        }

        /*-------------------------*/
        /* INFO                    */
        /*-------------------------*/

        void Info(std::string_view msg) const {
            fmt::print(slfmt::color::INFO_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Info(std::string_view format, Args... args) const {
            Info(fmt::format(format, args...));
        }

        void Info(std::string_view msg, const std::exception &e) const {
            Info(fmt::format(msg, e.what()));
        }


        /*-------------------------*/
        /* WARNING				   */
        /*-------------------------*/

        void Warn(std::string_view msg) const {
            fmt::print(slfmt::color::WARN_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Warn(std::string_view format, Args... args) const {
            Warn(fmt::format(format, args...));
        }

        void Warn(std::string_view msg, const std::exception &e) const {
            Warn(fmt::format(msg, e.what()));
        }

        /*-------------------------*/
        /* ERROR                   */
        /*-------------------------*/

        void Error(std::string_view msg) const {
            fmt::print(slfmt::color::ERROR_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Error(std::string_view format, Args... args) const {
            Error(fmt::format(format, args...));
        }

        void Error(std::string_view msg, const std::exception &e) const {
            Error(fmt::format(msg, e.what()));
        }

        /*-------------------------*/
        /* FATAL                   */
        /*-------------------------*/

        void Fatal(std::string_view msg) const {
            fmt::print(slfmt::color::FATAL_COLOR, "{}: {}\n", clazz_, msg);
        }

        template<typename... Args>
        void Fatal(std::string_view format, Args... args) const {
            Fatal(fmt::format(format, args...));
        }

        void Fatal(std::string_view msg, const std::exception &e) const {
            Fatal(fmt::format(msg, e.what()));
        }
    };
}  // namespace slfmt

#endif // SLFMT_LOGGER_H
