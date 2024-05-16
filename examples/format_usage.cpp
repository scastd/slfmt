#include "slfmt.h"

int main(int argc, char *argv[]) {
    const slfmt::LogFormat lf = slfmt::LogFormat::Builder()
                                        .Timestamp("[", "]")
                                        .Level("(", ")")
                                        .Class()
                                        .ThreadId("[Thread-<", ">]")
                                        .Message()
                                        .Build();

    std::string string = lf.Format({ { "{C}", "TestClass" }, { "{L}", "INFO" }, { "{M}", "12345" } });
    fmt::print(string);

    return 0;
}
