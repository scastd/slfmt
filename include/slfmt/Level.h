/*
 * slfmt - A simple logging library for C++
 *
 * Level.h - Log levels for slfmt
 *
 * Copyright (c) 2023 Samuel Castrillo Domínguez
 * All rights reserved.
 *
 * For more information, please see the LICENSE file.
 */

#ifndef SLFMT_LEVEL_H
#define SLFMT_LEVEL_H

#include <string>

static const auto TRACE_LEVEL_STRING = "TRACE";
static const auto DEBUG_LEVEL_STRING = "DEBUG";
static const auto INFO_LEVEL_STRING = "INFO";
static const auto WARN_LEVEL_STRING = "WARN";
static const auto ERROR_LEVEL_STRING = "ERROR";
static const auto FATAL_LEVEL_STRING = "FATAL";
static const auto UNKNOWN_LEVEL_STRING = "UNKNOWN";

namespace slfmt {
    /**
     * @brief Log levels.
     */
    enum class Level : unsigned int { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, UNKNOWN };

    /**
     * @brief Converts a log level to a string.
     *
     * @param level The level to convert.
     * @return The string representation of the level.
     */
    static std::string LevelToString(const Level &level) {
        switch (level) {
            case Level::TRACE: return TRACE_LEVEL_STRING;
            case Level::DEBUG: return DEBUG_LEVEL_STRING;
            case Level::INFO: return INFO_LEVEL_STRING;
            case Level::WARN: return WARN_LEVEL_STRING;
            case Level::ERROR: return ERROR_LEVEL_STRING;
            case Level::FATAL: return FATAL_LEVEL_STRING;
            default: return UNKNOWN_LEVEL_STRING;
        }
    }

    /**
     * @brief Converts a string to a log level.
     *
     * @param level The string to convert.
     * @return The log level.
     */
    static Level StringToLevel(const std::string_view &level) {
        if (level == TRACE_LEVEL_STRING) return Level::TRACE;
        if (level == DEBUG_LEVEL_STRING) return Level::DEBUG;
        if (level == INFO_LEVEL_STRING) return Level::INFO;
        if (level == WARN_LEVEL_STRING) return Level::WARN;
        if (level == ERROR_LEVEL_STRING) return Level::ERROR;
        if (level == FATAL_LEVEL_STRING) return Level::FATAL;

        return Level::UNKNOWN;
    }
} // namespace slfmt

#endif // SLFMT_LEVEL_H
