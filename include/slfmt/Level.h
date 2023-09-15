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
            return "TRACE";
        } else if (level == Level::DEBUG) {
            return "DEBUG";
        } else if (level == Level::INFO) {
            return "INFO";
        } else if (level == Level::WARN) {
            return "WARN";
        } else if (level == Level::ERROR) {
            return "ERROR";
        } else if (level == Level::FATAL) {
            return "FATAL";
        } else {
            return "UNKNOWN";
        }
    }

    /**
     * @brief Converts a string to a log level.
     *
     * @param level The string to convert.
     * @return The log level.
     */
    static inline Level StringToLevel(const std::string_view &level) {
        if (level == "TRACE") {
            return Level::TRACE;
        } else if (level == "DEBUG") {
            return Level::DEBUG;
        } else if (level == "INFO") {
            return Level::INFO;
        } else if (level == "WARN") {
            return Level::WARN;
        } else if (level == "ERROR") {
            return Level::ERROR;
        } else if (level == "FATAL") {
            return Level::FATAL;
        } else {
            return Level::UNKNOWN;
        }
    }
} // namespace slfmt

#endif // SLFMT_LEVEL_H
