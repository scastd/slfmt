#include <slfmt.h>

int main(int, char *[]) {
    const auto logger = slfmt::Logger::GetLogger("main");
    logger->Trace("Hello, {}!", "world");
    logger->Debug("Hello, {}!", "world");
    logger->Info("Hello, {}!", "world");
    logger->Warn("Hello, {}!", "world");
    logger->Error("Hello, {}!", "world");
    logger->Fatal("Hello, {}!", "world");
	return 0;
}
