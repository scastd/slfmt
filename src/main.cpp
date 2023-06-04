#include <slfmt.h>

class Example {
private:
    CLASS_LOGGER(logger_, Example);

public:
    Example() = default;
    ~Example() = default;

    static void test(const std::string &value) {
        logger_->Debug("Called with \"{}\", {}", value, SLFMT_VERSION_STRING);
    }
};

int main(int, char *[]) {
    Example::test("hello!");
    return 0;
}
