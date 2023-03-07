#include "ConsoleInput.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ArgsHelper {
  private:
    // types
    using vec_opts_t = std::vector<std::string>;

    // variables
    vec_opts_t args_vec;
    vec_opts_t::iterator vec_begin;
    vec_opts_t::iterator vec_end;
    inline static const std::string empty_string = "";

  public:
    ArgsHelper(int &argc, char *argv[])
    /*
     * Class constructor.
     */
    {
        for (int i = 1; i < argc; ++i) {
            this->args_vec.push_back(std::string(argv[i]));
        }
        // shrink capacity to actual size
        this->args_vec.shrink_to_fit();
        // get begin and end iterators
        vec_begin = this->args_vec.begin();
        vec_end = this->args_vec.end();
    }

    bool check_if_exists(const std::string &name) const
    /*
     * Check if a single argument exists.
     * E.g., ./main.o -h
     *
     * Usage:
     * if (args_helper.check_if_exists("-h")) {
     *     // do things
     * }
     */
    {
        return (std::find(vec_begin, vec_end, name) != vec_end);
    }

    bool check_if_exists(const std::string &name1, const std::string &name2) const
    /*
     * Check if two arguments exists.
     * E.g., ./main.o -h || ./main.o --help
     *
     * Usage:
     * if (args_helper.check_if_exists("-h", "--help")) {
     *     // do things
     * }
     */
    {
        return (this->check_if_exists(name1) || this->check_if_exists(name2));
    }

    const std::string &get_keyword_pair(const std::string &name) const
    /*
     * Get keyword argument by name.
     * E.g., ./main.o --csv "file.csv"
     *
     * Usage:
     *     const std::string &filename = args_helper.get_keyword_pair("-c", "--csv");
     *     if (!filename.empty()) {
     *         // do things
     *     }
     */
    {
        // get iterator to the first element is equal to name.
        vec_opts_t::const_iterator itr = std::find(vec_begin, vec_end, name);
        // get element AFTER that iterator (+1)
        if (itr != vec_end && ++itr != vec_end) {
            return *itr;
        }
        std::cerr << "ERROR: argument '" << name << "' doesn't have a value.\n";
        return this->empty_string;
    }
};

bool load_text_from_disk(const std::string &filename, std::string &s)
/*
 * Read txt file from disk and append it to the "s" variable.
 */
{
    std::string line;
    std::ifstream file_str(filename);  // filehandle is closed automatically
    if (!file_str) {
        std::cerr << "ERROR: could not open ifstream for '" << filename
                  << "', possibly due to missing permissions to the filesystem.\n";
        return false;
    }
    // while exists, append to string with newline
    while (std::getline(file_str, line)) {
        s += line + '\n';
    }
    // check if empty string
    if (s.empty()) {
        std::cerr << "ERROR: loaded file is empty '" << filename
                  << "'.\n";
        return false;
    }
    return true;
}
namespace ConsoleInput {
void print_help(const char *program_name, const console_args_t &args)
{
    /*
     * Print help message to console, to be called using "-h" or "--help".
     */
    std::cout << "usage: "
              << program_name
              << " [-h | --help] [-f <filename>] [-s <string>]\n\n"
                 "options:\n"
                 "  -h | --help                 print this help message\n"
                 "  -f <filename>               filename to be processed (default: \""
              << args.filename << "\")\n"
              << "  -s <filename>               string to be processed\n";
}

bool parse_args(console_args_t &args)
{
    /*
     * Read filename or string input from commandline arguments.
     *
     * Return True if everything worked as expected, False if failed.
     */
    const ArgsHelper args_helper(args.argc, args.argv);
    if (args_helper.check_if_exists("-h", "--help")) {
        print_help(args.argv[0], args);
        return false;
    }
    // -- string ---
    // check for "-s", do not use fallback if empty
    if (args_helper.check_if_exists("-s")) {
        args.final_str = args_helper.get_keyword_pair("-s");
        if (args.final_str.empty()) {
            std::cerr << "ERROR: please provide a non-empty string.\n";
            return false;
        }
        args.is_file_mode = false;
    }
    else {
        // --- file.txt ---
        // check for "-f", but use "file.txt" as fallback if empty
        if (args_helper.check_if_exists("-f")) {
            args.filename = args_helper.get_keyword_pair("-f");
            if (args.filename.empty()) {
                std::cerr << "ERROR: please provide a non-empty filename.\n";
                return false;
            }
        }
        // file doesn't exist
        if (!std::filesystem::exists(args.filename)) {
            std::cerr << "ERROR: filename provided doesn't exist: '" << args.filename
                      << "'.\n";
            return false;
        }
        if (!load_text_from_disk(args.filename, args.final_str)) {
            std::cerr << "ERROR: couldn't load filename provided by user '"
                      << args.filename << "'.\n";
            return false;
        }
        // file exists, all good
        args.is_file_mode = true;
    }
    return true;
}
}  // namespace ConsoleInput
