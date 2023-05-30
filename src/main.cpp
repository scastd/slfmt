#include <slfmt.h>

int main(int, char *[]) {
	fmt::print(slfmt::color::magenta, "Hello, {}!\n", "world");
	return 0;
}
