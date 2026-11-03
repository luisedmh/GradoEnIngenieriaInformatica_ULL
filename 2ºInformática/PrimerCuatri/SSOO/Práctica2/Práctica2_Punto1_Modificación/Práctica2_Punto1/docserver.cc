#include <expected>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <fcntl.h>      //open()
#include <unistd.h>     //close()
#include <cstring>

#include "docserver_tools.h"
#include "SafeFD.h"
#include "SafeMap.h"

int main(int argc, char* argv[]) {
    auto options = parse_args(argc, argv);
    if (!options.has_value()) {
        if (options.error() == parse_args_errors::missing_argument) {
            std::cerr << "Error: Falta un argumento " << std::endl;
        } else
        if (options.error() == parse_args_errors::unknown_option) {
            std::cerr << "Error: El argumento es erróneo" << std::endl;
        } else 
        if (options.error() == parse_args_errors::over_files) {
            std::cerr << "Error: Hay demasiados archivos" << std::endl;
        }
        return EXIT_FAILURE;
    }
    if (options.value().show_help) {
        Usage();
        return EXIT_SUCCESS;
    }
    auto input_result = read_all(options.value());
    if (!input_result.has_value()) {
        if (input_result.error() == EACCES) {
            send_response("403 Forbidden", "");
            std::cerr << "Error " << input_result.error() << " " << std::strerror(input_result.error()) << std::endl;
            return EXIT_SUCCESS;
        } else 
        if (input_result.error() == ENOENT) {
            send_response("404 Not Found", "");
            std::cerr << "Error " << input_result.error() << " " << std::strerror(input_result.error()) << std::endl;
            return EXIT_SUCCESS;
        }else 
        if (input_result.error() == 1024) {
            std::cerr << "Error " << input_result.error() << std::endl;
            return EXIT_FAILURE;
        } else {
            std::cerr << "Error " << input_result.error() << std::endl;
            return EXIT_FAILURE;
        }
        
    } else {
        SafeMap content = std::move(input_result.value());
        if (options.value().verbose) {
            std::cerr << "write: se imprime la salida" << std::endl;
        }
        if (content.get().empty()) {
            send_response(std::format("Content-Length: {}", content.get().size()), "Error: El archivo está vacío");
            return EXIT_SUCCESS;
        } else {
            send_response(std::format("Content-Length: {}", content.get().size()), content.get());
            return EXIT_SUCCESS;
        }
    }
}
