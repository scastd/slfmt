#include "slfmt.h"
#include "slfmt/Level.h"

class TestClass {
private:
    SLFMT_CONSOLE_LOGGER_FIELD(s_logger, TestClass);

public:
    void Test(std::string_view s) const {
        s_logger->Trace("{}", "Test 0");
        s_logger->Debug("{}", "Test 1");
        s_logger->Info("{}", "Test 2");
        s_logger->Warn("{}, {} ", "Test 3", s);
        s_logger->Error("{}", "Test 4");
        s_logger->Fatal("{}", "Test 5");
    }
};

class TestClass2 {
private:
    SLFMT_FILE_LOGGER_FIELD(s_logger, TestClass2);

public:
    void Test(std::string_view s) const {
        s_logger->Info("{}", slfmt::LevelToString(slfmt::Level::INFO));
        s_logger->Info("{}", "Test 1");
        s_logger->Debug("{}", "Test 2");
        s_logger->Trace("{}", "Test 3");
        s_logger->Warn("{}, {}", "Test 4", s);
    }
};

int main(int argc, char *argv[]) {
    const TestClass test1;
    const TestClass2 test2;
    test1.Test("Example parameter");
    test2.Test("Second instance");
    return 0;
}
