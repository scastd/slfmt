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

static const char *const TRACE_LEVEL_STRING = "TRACE";
static const char *const DEBUG_LEVEL_STRING = "DEBUG";
static const char *const INFO_LEVEL_STRING = "INFO";
static const char *const WARN_LEVEL_STRING = "WARN";
static const char *const ERROR_LEVEL_STRING = "ERROR";
static const char *const FATAL_LEVEL_STRING = "FATAL";
static const char *const UNKNOWN_LEVEL_STRING = "UNKNOWN";

namespace slfmt {
    /**
     * @brief Log levels.
     */
    enum class Level { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, UNKNOWN };

    /**
     * @brief Converts a log level to a string.
     *
     * @param level The level to convert.
     * @return The string representation of the level.
     */
    static inline std::string LevelToString(const Level &level) {
        if (level == Level::TRACE) {
            return TRACE_LEVEL_STRING;
        } else if (level == Level::DEBUG) {
            return DEBUG_LEVEL_STRING;
        } else if (level == Level::INFO) {
            return INFO_LEVEL_STRING;
        } else if (level == Level::WARN) {
            return WARN_LEVEL_STRING;
        } else if (level == Level::ERROR) {
            return ERROR_LEVEL_STRING;
        } else if (level == Level::FATAL) {
            return FATAL_LEVEL_STRING;
        } else {
            return UNKNOWN_LEVEL_STRING;
        }
    }

    /**
     * @brief Converts a string to a log level.
     *
     * @param level The string to convert.
     * @return The log level.
     */
    static inline Level StringToLevel(const std::string_view &level) {
        if (level == TRACE_LEVEL_STRING) {
            return Level::TRACE;
        } else if (level == DEBUG_LEVEL_STRING) {
            return Level::DEBUG;
        } else if (level == INFO_LEVEL_STRING) {
            return Level::INFO;
        } else if (level == WARN_LEVEL_STRING) {
            return Level::WARN;
        } else if (level == ERROR_LEVEL_STRING) {
            return Level::ERROR;
        } else if (level == FATAL_LEVEL_STRING) {
            return Level::FATAL;
        } else {
            return Level::UNKNOWN;
        }
    }
} // namespace slfmt

#endif // SLFMT_LEVEL_H
