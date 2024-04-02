#include "slfmt.h"
#include "slfmt/Level.h"

class TestClass {
private:
    static inline const auto s_logger = slfmt::LogManager::GetFileLogger("TestClass", s_defaultLoggerFilename,
                                                                         1024 * 5);

public:
    void Test(std::string_view s) const {
        for (int i = 0; i < 100000; ++i) {
            s_logger->Info("Test message with number: {}", i);
        }
    }
};

int main(int argc, char *argv[]) {
    const TestClass test1;

    test1.Test("Example parameter");

    return 0;
}
