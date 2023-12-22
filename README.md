# SLFMT (Simple Logging using {FMT})

SLFMT is a logging library that uses [fmt](https://github.com/fmtlib/fmt) to format log messages.
It is heavily inspired by [log4j](https://www.slf4j.org/), being an easy-to-use, header-only library that can be used
in any C++ project.

## Features

- Class level logging.
- Log levels: trace, debug, info, warn, error, fatal.
- Logger messages are formatted using fmt (see full list of
  features [here](https://github.com/fmtlib/fmt/blob/master/README.rst#features)).
- Logger messages contain the class from which the message was logged.
- You can modify the log message format by modifying the `SLFMT_LOG_FORMAT` macro.
- Logs are written to the console or to a file.

## Getting Started

There are several ways to use this library in your project.

### Using CMake

Download the repository in your project and add the `include` directory to your include directories.
If you use CMake, you can use the `add_subdirectory` command to add the library to your project.

```cmake
add_subdirectory(path/to/slfmt)
```

Then, link the library to your target:

```cmake
target_link_libraries(your_target PRIVATE slfmt)
```

### Using CPM.cmake

If you use [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) in your project, you can add the library
as a dependency in your `CMakeLists.txt` file with the following command:

```cmake
CPMAddPackage("gh:scastd/slfmt#0.1.0")
```

The link step is the same as the one described in the previous section.

```cmake
target_link_libraries(your_target PRIVATE slfmt)
```

## Declaration

### Defining class loggers

There are two ways to use the library: explicitly creating the loggers or using macros to create them automatically.

#### Creating loggers explicitly

This is the **verbose** way to create a logger; by using the `slfmt::LogManager::GetLogger` method to
declare a static field in the class.

```c++
static inline const auto logger = slfmt::LogManager::GetLogger("Class");
```

The `GetLogger` method takes the name of the class as a parameter and returns a `std::unique_ptr` to a console logger.
If you want to create a file logger, you can use the `GetFileLogger` method instead.

```c++
static inline const auto logger = slfmt::LogManager::GetFileLogger("Class", "path/to/file.log");
```

#### Using macros

This is the **recommended** way to create a logger because it automatically generates the static field depending on the
logger type you want.
There are several macros you can use:

- `SLFMT_CONSOLE_LOGGER`: Creates a console logger.
- `SLFMT_FILE_LOGGER`: Creates a file logger.
- `SLFMT_FILE_LOGGER_NAME`: Creates a file logger with the specified name.
- `SLFMT_CONSOLE_LOGGER_FIELD`: Creates a static field for a console logger.
- `SLFMT_FILE_LOGGER_FIELD`: Creates a static field for a file logger.
- `SLFMT_FILE_LOGGER_NAME_FIELD`: Creates a static field for a file logger with the specified name.
- `SLFMT_COMBINED_LOGGER_FIELD`: Creates a static field for a combined logger. You pass as parameters the loggers you
  want to combine.
- `SLFMT_FILE_CONSOLE_COMBINED_LOGGER_FIELDS`: Creates a static field for a combined logger composed of a file logger
  and a console logger.

### Using the loggers

Any logger can be used to log messages of different levels (each one uses a different color in the console):

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

```text
Timestamp Level (Class) [ThreadID] Message
```

You can customize the log format by modifying the `SLFMT_LOG_FORMAT` macro.

# License

This project is licensed under the MIT License: see the [LICENSE](LICENSE.txt) file for details.

# Future work

- [x] Add support for logging to file.
    - [ ] Rotating log files.
    - [ ] Log file size limit.
  - [x] Log file path / name.
- [ ] Make a builder for log format.
- [ ] Add support for custom log levels.
- [ ] Add support for custom log level colors.
