#ifndef SLFMT_COLOR_H
#define SLFMT_COLOR_H

#include <fmt/color.h>

namespace slfmt::color {
	constexpr inline auto red = fg(fmt::color::red);
	constexpr inline auto green = fg(fmt::color::green);
	constexpr inline auto blue = fg(fmt::color::cornflower_blue);
	constexpr inline auto yellow = fg(fmt::color::yellow);
	constexpr inline auto cyan = fg(fmt::color::cyan);
	constexpr inline auto magenta = fg(fmt::color::magenta);
	constexpr inline auto white = fg(fmt::color::white);
	constexpr inline auto gray = fg(fmt::color::gray);
	constexpr inline auto black = fg(fmt::color::black);

	constexpr inline auto red_bg = bg(fmt::color::red);
	constexpr inline auto green_bg = bg(fmt::color::green);
	constexpr inline auto blue_bg = bg(fmt::color::cornflower_blue);
	constexpr inline auto yellow_bg = bg(fmt::color::yellow);
	constexpr inline auto cyan_bg = bg(fmt::color::cyan);
	constexpr inline auto magenta_bg = bg(fmt::color::magenta);
	constexpr inline auto white_bg = bg(fmt::color::white);
	constexpr inline auto gray_bg = bg(fmt::color::gray);
	constexpr inline auto black_bg = bg(fmt::color::black);

	constexpr inline auto bold = fmt::emphasis::bold;
	constexpr inline auto italic = fmt::emphasis::italic;
	constexpr inline auto underline = fmt::emphasis::underline;
	constexpr inline auto strikethrough = fmt::emphasis::strikethrough;

	constexpr inline auto TRACE_COLOR = white;
	constexpr inline auto DEBUG_COLOR = magenta;
	constexpr inline auto INFO_COLOR = blue;
	constexpr inline auto WARN_COLOR = yellow;
	constexpr inline auto ERROR_COLOR = red;
	constexpr inline auto FATAL_COLOR = red | bold | underline;
}

#endif // SLFMT_COLOR_H
