/*
 * slfmt - A simple logging library for C++
 *
 * Color.h - Color definitions for slfmt
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
#ifdef _WIN32
    // This is a hack to remove colors on Windows because fmt::text_style doesn't work on Windows.
    // Temporary solution until fmt::text_style works on Windows.
    inline const fmt::text_style NO_COLOR = fmt::text_style();

    inline const fmt::text_style red = NO_COLOR;
    inline const fmt::text_style green = NO_COLOR;
    inline const fmt::text_style blue = NO_COLOR;
    inline const fmt::text_style yellow = NO_COLOR;
    inline const fmt::text_style cyan = NO_COLOR;
    inline const fmt::text_style magenta = NO_COLOR;
    inline const fmt::text_style white = NO_COLOR;
    inline const fmt::text_style gray = NO_COLOR;
    inline const fmt::text_style black = NO_COLOR;

    inline const fmt::text_style red_bg = NO_COLOR;
    inline const fmt::text_style green_bg = NO_COLOR;
    inline const fmt::text_style blue_bg = NO_COLOR;
    inline const fmt::text_style yellow_bg = NO_COLOR;
    inline const fmt::text_style cyan_bg = NO_COLOR;
    inline const fmt::text_style magenta_bg = NO_COLOR;
    inline const fmt::text_style white_bg = NO_COLOR;
    inline const fmt::text_style gray_bg = NO_COLOR;
    inline const fmt::text_style black_bg = NO_COLOR;

    inline const fmt::text_style bold = NO_COLOR;
    inline const fmt::text_style italic = NO_COLOR;
    inline const fmt::text_style underline = NO_COLOR;
    inline const fmt::text_style strikethrough = NO_COLOR;

    inline const fmt::text_style TRACE_COLOR = NO_COLOR;
    inline const fmt::text_style DEBUG_COLOR = NO_COLOR;
    inline const fmt::text_style INFO_COLOR = NO_COLOR;
    inline const fmt::text_style WARN_COLOR = NO_COLOR;
    inline const fmt::text_style ERROR_COLOR = NO_COLOR;
    inline const fmt::text_style FATAL_COLOR = NO_COLOR;
#else
    inline const fmt::text_style NO_COLOR = fmt::text_style();

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
#endif
} // namespace slfmt::color

#endif // SLFMT_COLOR_H
