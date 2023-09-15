/*
 * slfmt - A simple logging library for C++
 *
 * Version.h - Version information
 *
 * Copyright (c) 2023 Samuel Castrillo Domínguez
 * All rights reserved.
 *
 * For more information, please see the LICENSE file.
 */

#ifndef SLFMT_VERSION_H
#define SLFMT_VERSION_H

#pragma once

#include <fmt/format.h>

const long SLFMT_VERSION_MAJOR = 0;
const long SLFMT_VERSION_MINOR = 1;
const long SLFMT_VERSION_PATCH = 0;

const long SLFMT_VERSION = (SLFMT_VERSION_MAJOR * 10000 + SLFMT_VERSION_MINOR * 100 + SLFMT_VERSION_PATCH);

const std::string SLFMT_VERSION_STRING =
        fmt::format("{}.{}.{}", SLFMT_VERSION_MAJOR, SLFMT_VERSION_MINOR, SLFMT_VERSION_PATCH);

#endif // SLFMT_VERSION_H
