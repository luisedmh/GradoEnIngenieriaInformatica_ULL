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
    auto socket = make_socket(options.value());
    if (!socket.has_value()) {
        std::cerr << "Error "<< socket.error() <<": Creación del socket. " << std::strerror(socket.error()) <<std::endl;
        return EXIT_FAILURE;
    }
    SafeFD socket_fd = std::move(socket.value());
    int listen = listen_connection(socket_fd, options.value());
    if (listen < 0) {
        std::cerr << "Error " << listen << ": El socket no pudo iniciar la escucha. " << std::strerror(listen) << std::endl;
        return EXIT_FAILURE;
    }
    while(true) {
        sockaddr_in client_addr {};
        auto accept = accept_connection(socket_fd, client_addr, options.value());
        if (!accept.has_value()) {
            std::cerr << "Error "<< accept.error() <<" : No se pudo aceptar la conexión. " << std::strerror(accept.error()) << std::endl;
        }
        auto input_result = read_all(options.value());
        if (!input_result.has_value()) {
            if (input_result.error() == EACCES) {
                send_response(accept.value(), "403 Forbidden", "", options.value());
                std::cerr << "Error " << input_result.error() << " " << std::strerror(input_result.error()) << std::endl;
            } else 
            if (input_result.error() == ENOENT) {
                send_response(accept.value(), "404 Not Found", "", options.value());
                std::cerr << "Error " << input_result.error() << " " << std::strerror(input_result.error()) << std::endl;
            } else {
                std::cerr << "Error " << input_result.error() << std::endl;
            }
            //std::cout << "cierre1" << std::endl; 
            return EXIT_FAILURE;
        } else {
            SafeMap content = std::move(input_result.value());
            if (content.get().empty()) {
                int respond = send_response(accept.value(), std::format("Content-Length: {}", content.get().size()), "Error: El archivo está vacío", options.value());
                if (respond < 0) {
                    std::cerr << "Error "<< respond <<": No se pudo enviar la respuesta" << std::strerror(respond) << std::endl;
                    //std::cout << "cierre4" << std::endl;
                    return EXIT_FAILURE;
                }
                //std::cout << "cierre2" << std::endl;
                return EXIT_SUCCESS;
            } else {
                int response = send_response(accept.value(), std::format("Content-Length: {}", content.get().size()), content.get(), options.value());
                if (response == ECONNRESET) {
                    std::cerr << "El otro socket no pudo recibir la respuesta" << std::endl;
                } else 
                if (response < 0) {
                    std::cerr << "Error " << response <<": No se pudo enviar la respuesta correctamente" << std::strerror(response) << std::endl;
                }

                //std::cout << "cierre3" << std::endl;
                //return EXIT_SUCCESS;
            }
        }
    }
}
