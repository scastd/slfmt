# SLFMT (Simple Logging using {FMT})

SLFMT is a logging library that uses the [fmt](https://github.com/fmtlib/fmt) library to format log messages
inspired by [slf4j](https://www.slf4j.org/). It is an easy to use, header-only library that can be used in any C++
project.

## Features

- Class level logging.
- Log levels: trace, debug, info, warn, error, fatal.
- Logger messages are formatted using fmt (see full list of
  features [here](https://github.com/fmtlib/fmt/blob/master/README.rst#features)).
- Logger messages contain the class from which the message was logged (de-mangling
  using [abi::__cxa_demangle](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html)).
- You can modify the log message format by modifying the `SLFMT_LOG_FORMAT` macro.

## Getting Started

You have to download the repository in your project and add the `include` directory to your include directories.
If you use CMake, you can use the `add_subdirectory` command to add the library to your project.

```cmake
add_subdirectory(slfmt)
```

## Usage

### Basic usage

There are two ways to use the logger. The first is to use the `SLFMT_LOGGER` macro inside the private fields of the
class:

```c++
SLFMT_LOGGER(logger, Class);
```

The second is to use the `slfmt::Logger::GetLogger` method:

```c++
static inline const auto logger = slfmt::Logger::GetLogger<Class>();
```

The logger can then be used to log messages of different levels (each one corresponds to a different color in the
console):

```c++
logger->Trace("This is a trace message");  // white
logger->Debug("This is a debug message");  // magenta
logger->Info("This is an info message");   // blue
logger->Warn("This is a warn message");    // yellow
logger->Error("This is an error message"); // red
logger->Fatal("This is a fatal message");  // red | bold | underline
```

Or you can call the `Log` method directly and specify the log level:

```c++
logger->Log(slfmt::LogLevel::Trace, "This is a trace message");  // white
logger->Log(slfmt::LogLevel::Debug, "This is a debug message");  // magenta
logger->Log(slfmt::LogLevel::Info, "This is an info message");   // blue
logger->Log(slfmt::LogLevel::Warn, "This is a warn message");    // yellow
logger->Log(slfmt::LogLevel::Error, "This is an error message"); // red
logger->Log(slfmt::LogLevel::Fatal, "This is a fatal message");  // red | bold | underline
```

### Custom log format

The default log format is:

```c++
"[{level}] {class}: {message}\n"
```

# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

# Future work

- [ ] Add support for logging to file.
    - [ ] Rotating log files.
    - [ ] Log file size limit.
    - [ ] Log file path / name.
- [ ] Make a builder for log format.
- [ ] Add support for custom log levels.
- [ ] Add support for custom log level colors.
