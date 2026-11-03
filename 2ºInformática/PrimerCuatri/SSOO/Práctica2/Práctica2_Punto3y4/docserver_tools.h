#include <expected>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <format>
#include <fcntl.h>      //open()
#include <unistd.h>     //close(), acces()
#include <sys/mman.h>   // mmap()
#include <unistd.h>     // read()
#include <cerrno>       // errno
#include <netinet/ip.h> // socket(), bind()
#include <sys/wait.h>   // waitpid()

#include "SafeFD.h"
#include "SafeMap.h"

typedef std::vector<std::string> exec_environment;

enum class parse_args_errors {
    missing_argument,
    unknown_option,
    extra_parameters,
    function_error
};

struct program_options {
    bool show_help = false;
    bool verbose = false;
    bool port = false;
    bool base = false;
    uint16_t port_num = 8080;
    std::string path;
    std::string path_result;
    std::vector<std::string> additional_args;
};

struct execute_program_error {
    int exit_code;
    int error_code;
};

std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]);
std::expected<SafeFD, int> open_file(const std::string& path, int flags, mode_t mode);
std::expected<SafeMap, int> read_all(const program_options& options);
void Usage();
int send_response(const SafeFD& socket, std::string_view header, std::string_view body, const program_options& options);
std::expected<SafeFD, int> make_socket(const program_options& options);
std::string getenv(const std::string& name);
int listen_connection(const SafeFD& socket, const program_options& options);
std::expected<SafeFD, int> accept_connection(const SafeFD& socket, sockaddr_in& client_addr, const program_options& options);
std::expected<std::string, int> receive_request(const SafeFD& socket, size_t max_size, const program_options& options);
std::expected<std::string, execute_program_error> execute_program(const exec_environment& env, const program_options& options);