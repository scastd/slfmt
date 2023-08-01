/*
 * slfmt - A simple logging library for C++
 *
 * color.h - Color definitions for slfmt
 *
 * Copyright (c) 2023 Samuel Castrillo Domínguez
 * All rights reserved.
 *
 * For more information, please see the LICENSE file.
 */

#ifndef SLFMT_COLOR_H
#define SLFMT_COLOR_H

#include <fmt/color.h>

namespace slfmt::color {
    inline const fmt::text_style red = fg(fmt::color::red);
    inline const fmt::text_style green = fg(fmt::color::green);
    inline const fmt::text_style blue = fg(fmt::color::cornflower_blue);
    inline const fmt::text_style yellow = fg(fmt::color::yellow);
    inline const fmt::text_style cyan = fg(fmt::color::cyan);
    inline const fmt::text_style magenta = fg(fmt::color::magenta);
    inline const fmt::text_style white = fg(fmt::color::white);
    inline const fmt::text_style gray = fg(fmt::color::gray);
    inline const fmt::text_style black = fg(fmt::color::black);

    inline const fmt::text_style red_bg = bg(fmt::color::red);
    inline const fmt::text_style green_bg = bg(fmt::color::green);
    inline const fmt::text_style blue_bg = bg(fmt::color::cornflower_blue);
    inline const fmt::text_style yellow_bg = bg(fmt::color::yellow);
    inline const fmt::text_style cyan_bg = bg(fmt::color::cyan);
    inline const fmt::text_style magenta_bg = bg(fmt::color::magenta);
    inline const fmt::text_style white_bg = bg(fmt::color::white);
    inline const fmt::text_style gray_bg = bg(fmt::color::gray);
    inline const fmt::text_style black_bg = bg(fmt::color::black);

    inline const fmt::text_style bold = fmt::emphasis::bold;
    inline const fmt::text_style italic = fmt::emphasis::italic;
    inline const fmt::text_style underline = fmt::emphasis::underline;
    inline const fmt::text_style strikethrough = fmt::emphasis::strikethrough;

    inline const fmt::text_style TRACE_COLOR = white;
    inline const fmt::text_style DEBUG_COLOR = magenta;
    inline const fmt::text_style INFO_COLOR = blue;
    inline const fmt::text_style WARN_COLOR = yellow;
    inline const fmt::text_style ERROR_COLOR = red;
    inline const fmt::text_style FATAL_COLOR = red | bold | underline;
    inline const fmt::text_style NO_COLOR = fmt::text_style();
} // namespace slfmt::color

#endif // SLFMT_COLOR_H
