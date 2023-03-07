#include "ConsoleInput.hpp"
#include "WordParser.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    ConsoleInput::console_args_t args;  // struct, because passing 5 variables is pain
    args.argc = argc;
    args.argv = argv;
    // default values that might be overwritten based on user input
    args.is_file_mode = true;    // try to read "file.txt" by default even if no flag provided
    args.filename = "file.txt";  // file must exist, unless string provided using "-s <text>"
    if (ConsoleInput::parse_args(args)) {
        WordParser::WordParser parser(args.final_str);
        parser.run();
    }
    return 0;
}
