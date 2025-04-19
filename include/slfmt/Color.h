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
    inline constexpr auto NO_COLOR = fmt::text_style();

    inline constexpr auto red = NO_COLOR;
    inline constexpr auto green = NO_COLOR;
    inline constexpr auto blue = NO_COLOR;
    inline constexpr auto yellow = NO_COLOR;
    inline constexpr auto cyan = NO_COLOR;
    inline constexpr auto magenta = NO_COLOR;
    inline constexpr auto white = NO_COLOR;
    inline constexpr auto gray = NO_COLOR;
    inline constexpr auto black = NO_COLOR;

    inline constexpr auto red_bg = NO_COLOR;
    inline constexpr auto green_bg = NO_COLOR;
    inline constexpr auto blue_bg = NO_COLOR;
    inline constexpr auto yellow_bg = NO_COLOR;
    inline constexpr auto cyan_bg = NO_COLOR;
    inline constexpr auto magenta_bg = NO_COLOR;
    inline constexpr auto white_bg = NO_COLOR;
    inline constexpr auto gray_bg = NO_COLOR;
    inline constexpr auto black_bg = NO_COLOR;

    inline constexpr auto bold = NO_COLOR;
    inline constexpr auto italic = NO_COLOR;
    inline constexpr auto underline = NO_COLOR;
    inline constexpr auto strikethrough = NO_COLOR;

    inline constexpr auto TRACE_COLOR = NO_COLOR;
    inline constexpr auto DEBUG_COLOR = NO_COLOR;
    inline constexpr auto INFO_COLOR = NO_COLOR;
    inline constexpr auto WARN_COLOR = NO_COLOR;
    inline constexpr auto ERROR_COLOR = NO_COLOR;
    inline constexpr auto FATAL_COLOR = NO_COLOR;
#else
    inline constexpr auto NO_COLOR = fmt::text_style();

    inline constexpr auto red = fg(fmt::color::red);
    inline constexpr auto green = fg(fmt::color::green);
    inline constexpr auto blue = fg(fmt::color::cornflower_blue);
    inline constexpr auto yellow = fg(fmt::color::yellow);
    inline constexpr auto cyan = fg(fmt::color::cyan);
    inline constexpr auto magenta = fg(fmt::color::magenta);
    inline constexpr auto white = fg(fmt::color::white);
    inline constexpr auto gray = fg(fmt::color::gray);
    inline constexpr auto black = fg(fmt::color::black);

    inline constexpr auto red_bg = bg(fmt::color::red);
    inline constexpr auto green_bg = bg(fmt::color::green);
    inline constexpr auto blue_bg = bg(fmt::color::cornflower_blue);
    inline constexpr auto yellow_bg = bg(fmt::color::yellow);
    inline constexpr auto cyan_bg = bg(fmt::color::cyan);
    inline constexpr auto magenta_bg = bg(fmt::color::magenta);
    inline constexpr auto white_bg = bg(fmt::color::white);
    inline constexpr auto gray_bg = bg(fmt::color::gray);
    inline constexpr auto black_bg = bg(fmt::color::black);

    inline constexpr auto bold = fmt::emphasis::bold;
    inline constexpr auto italic = fmt::emphasis::italic;
    inline constexpr auto underline = fmt::emphasis::underline;
    inline constexpr auto strikethrough = fmt::emphasis::strikethrough;

    inline constexpr auto TRACE_COLOR = white;
    inline constexpr auto DEBUG_COLOR = magenta;
    inline constexpr auto INFO_COLOR = blue;
    inline constexpr auto WARN_COLOR = yellow;
    inline constexpr auto ERROR_COLOR = red;
    inline constexpr auto FATAL_COLOR = red | bold | underline;
#endif
} // namespace slfmt::color

#endif // SLFMT_COLOR_H
