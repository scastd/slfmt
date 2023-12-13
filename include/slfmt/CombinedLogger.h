#ifndef SLFMT_COMBINED_LOGGER_H
#define SLFMT_COMBINED_LOGGER_H

#include "LoggerBase.h"
#include <vector>

namespace slfmt {
    class CombinedLogger : public LoggerBase {
    public:
        CombinedLogger(const std::string_view &clazz, std::vector<std::unique_ptr<LoggerBase>> loggers)
            : LoggerBase(clazz), m_loggers(std::move(loggers)) {}

        ~CombinedLogger() override {
            m_loggers.clear();
        }

    private:
        std::vector<std::unique_ptr<LoggerBase>> m_loggers;

        void Trace_Internal(std::string_view msg) override {
            for (const auto &logger: m_loggers) {
                logger->Trace(msg);
            }
        }

        void Debug_Internal(std::string_view msg) override {
            for (const auto &logger: m_loggers) {
                logger->Debug(msg);
            }
        }

        void Info_Internal(std::string_view msg) override {
            for (const auto &logger: m_loggers) {
                logger->Info(msg);
            }
        }

        void Warn_Internal(std::string_view msg) override {
            for (const auto &logger: m_loggers) {
                logger->Warn(msg);
            }
        }

        void Error_Internal(std::string_view msg) override {
            for (const auto &logger: m_loggers) {
                logger->Error(msg);
            }
        }

        void Fatal_Internal(std::string_view msg) override {
            for (const auto &logger: m_loggers) {
                logger->Fatal(msg);
            }
        }
    };
} // namespace slfmt

#endif // SLFMT_COMBINED_LOGGER_H
