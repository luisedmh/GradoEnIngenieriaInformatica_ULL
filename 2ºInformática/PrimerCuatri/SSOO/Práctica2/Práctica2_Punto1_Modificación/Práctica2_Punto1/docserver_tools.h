#include <expected>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <format>
#include <fcntl.h>      //open()
#include <unistd.h>     //close()
#include <sys/mman.h>   // mmap()
#include <unistd.h>     // read()
#include <cerrno>       // errno

#include "SafeFD.h"
#include "SafeMap.h"

enum class parse_args_errors {
    missing_argument,
    unknown_option,
    over_files
};

struct program_options {
    bool show_help = false;
    bool verbose = false;
    bool x = false;
    std::string output_filename;
    std::vector<std::string> additional_args;
};

std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]);
std::expected<SafeMap, int> read_all(const program_options& options);
void Usage();
void send_response(std::string_view header, std::string_view body);
