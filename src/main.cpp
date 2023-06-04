#include <slfmt.h>

class Example {
private:
    SLFMT_LOGGER(logger_, Example);

public:
    Example() = default;
    ~Example() = default;

    static void test(const std::string &value) {
        logger_->Debug("Hello {}", value);
    }
};

int main(int, char *[]) {
    Example::test("world!");
    return 0;
}
