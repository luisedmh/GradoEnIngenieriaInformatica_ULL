#include <expected>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <fcntl.h>      //open()
#include <unistd.h>     //close()
#include <cstring>
#include <sstream>
#include <arpa/inet.h> //inet_ntoa()

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
        if (options.error() == parse_args_errors::extra_parameters) {
            std::cerr << "Error: Hay parámetros de más" << std::endl;
        } else
        if (options.error() == parse_args_errors::function_error) {
            std::cerr << "Error: Hay un problema con una función del sistema" << std::endl;
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
            return EXIT_FAILURE;
        }
        size_t max_size = 4096;
        auto receive_result = receive_request(accept.value(), max_size, options.value());
        if (!receive_result.has_value()) {
            if (receive_result.error() == ECONNRESET) {
                std::cerr << "Error " << socket.error() << ": Al recibir la dirección. " << std::strerror(receive_result.error()) << std::endl;
            }else {
                std::cerr << "Error " << socket.error() << ": Recibir la dirección" << std::strerror(receive_result.error()) << std::endl;
                return EXIT_FAILURE; 
            }
        } else {
            std::istringstream receive_stream(receive_result.value());
            std::string GET, second_path;
            receive_stream >> GET >> second_path;
            //std::cout << GET << second_path << std::endl;
            if (GET != "GET") {
                send_response(accept.value(), "400 bad request", "", options.value());
            } else {
                //std::cout << options.value().path << std::endl;
                bool is_bin = true;
                std::string bin = "/bin";
                for (unsigned int it = 0; it < 4; it++) {
                    if (second_path[it] != bin[it]) {
                        is_bin = false;
                        break;
                    }
                }
                if (is_bin) {
                    //std::cout << "Hola" << std::endl;
                    options.value().path_result = options.value().path + second_path;
                    //std::cerr << options.value().path_result;
                    exec_environment env_data;
                    env_data.emplace_back(options.value().path_result);
                    env_data.emplace_back(second_path);
                    env_data.emplace_back(std::to_string(options.value().port_num));
                    env_data.emplace_back(std::string(inet_ntoa(client_addr.sin_addr)));

                    //std::cerr << "Emplace";
                    auto input_result = execute_program(env_data, options.value());
                    //std::cerr << "Funcionó el execute" << std::endl;
                    if (!input_result.has_value()) {
                        if (input_result.error().error_code == EACCES) {
                            send_response(accept.value(), "403 Forbidden", "", options.value());
                        } else if (input_result.error().error_code == ENOENT) {
                            send_response(accept.value(), "404 Not Found", "", options.value());
                        } else {
                            send_response(accept.value(), "500 Internal Server Error", "", options.value());
                            std::cerr << "Error (" << input_result.error().error_code << ") en execute_program(): " << std::strerror(input_result.error().error_code) << std::endl;
                            return EXIT_FAILURE;
                        } 
                    } else {
                        //std::cerr << "Hola2" << std::endl;
                        int response_result = send_response(accept.value(), std::format("Content-Length: {}", input_result.value().length()), input_result.value(), options.value());
                        //std::cerr << "Hola3" << std::endl;
                        if (response_result < 0) {
                            std::cerr << "Error (" << response_result << ") en send_response(): " << std::strerror(response_result) << std::endl;
                        }
                    }
                    
                } else {
                    if (second_path[0] == '/') {
                        options.value().path_result = options.value().path + second_path;
                    } else {
                        options.value().path_result = options.value().path + "/" + second_path;
                    }
                    //std::cerr << "out";
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
                    } else {
                        SafeMap content = std::move(input_result.value());
                        if (content.get().empty()) {
                            int respond = send_response(accept.value(), std::format("Content-Length: {}", content.get().size()), "Error: El archivo está vacío", options.value());
                            if (respond < 0) {
                                std::cerr << "Error "<< respond <<": No se pudo enviar la respuesta" << std::strerror(respond) << std::endl;
                                //std::cout << "cierre4" << std::endl;
                            } else {
                                return EXIT_SUCCESS;
                            }
                            //std::cout << "cierre2" << std::endl;
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
                //std::cout << options.value().path << std::endl; 
            }
        }
    }
}
