#include "slfmt.h"
#include "slfmt/Level.h"

class CombinedLogger {
private:
    static inline const auto s_logger = slfmt::LogManager::GetCombinedLogger("CombinedLogger",
                                                                             SLFMT_FILE_LOGGER(CombinedLogger),
                                                                             SLFMT_CONSOLE_LOGGER(CombinedLogger));

public:
    void Test(std::string_view s) const {
        for (int i = 0; i < 20; ++i) {
            s_logger->Info("Test message with number: {}", i);
        }
    }
};

int main(int argc, char *argv[]) {
    const CombinedLogger test1;

    test1.Test("Example parameter");

    return 0;
}
