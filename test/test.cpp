#include <catch2/catch_test_macros.hpp>
#include <slfmt.h>

TEST_CASE("test version") {
	REQUIRE(SLFMT_VERSION_STRING == std::string("0.1.0"));
}
