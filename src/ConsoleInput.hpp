#pragma once

// libraries
#include <string>

// custom namespace
namespace ConsoleInput {

// types
struct console_args_t {
    int argc;
    char **argv;
    bool is_file_mode;
    std::string filename;
    std::string final_str;
};

// prototypes
bool parse_args(console_args_t &args);

}  // namespace ConsoleInput
