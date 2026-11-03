#include "docserver_tools.h"

std::string getenviroment(const std::string& name) {
    char* value = getenv(name.c_str());
    if (value) {
        return std::string(value);
    }
    else {
        return std::string();
    }
}

std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]) {
    std::vector<std::string_view> args(argv + 1, argv + argc);
    program_options options;
    std::string port_num = getenviroment("DOCSERVER_PORT");
    if (!port_num.empty()) {
        options.port_num = static_cast<uint16_t>(std::stoi(port_num));
    }
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == "-h" || *it == "--help") {
            options.show_help = true;
        } else 
        if (*it == "-v" || *it == "--verbose") {
            options.verbose = true; 
        } else 
        if (*it == "-p" || *it == "--verbose") {
            options.port = true;
            it++;
            if (it != end && !it->starts_with("-")) {
                options.port_num = static_cast<uint16_t>(std::stoi(std::string(*it)));
            } else {
                return std::unexpected(parse_args_errors::missing_argument);
            }
        } else 
        if (*it == "-b" || *it == "--base") {
            options.base = true;
            it++;
            if (it != end && !it->starts_with("-")) {
                options.path = std::string(*it);
            } else {
                return std::unexpected(parse_args_errors::missing_argument);
            }
        } else {
            if(it->starts_with("-")) {
                return std::unexpected(parse_args_errors::unknown_option);
            } else {
                return std::unexpected(parse_args_errors::extra_parameters);
            }
        }
    }
    if (!options.base) {
        std::string env_result = getenviroment("DOCSERVER_BASEDIR");
        if (env_result.empty()) {
            const size_t buf_size = 1024;
            char buffer [buf_size];
            if (getcwd(buffer, buf_size)) {
                options.path = buffer;
            } else {
                return std::unexpected(parse_args_errors::function_error);
            }
        } else {
            options.path = env_result;
        }
    }
    return options;
}

std::expected<SafeFD, int> open_file(const std::string& path, int flags, mode_t mode) {
    int fd = open(path.c_str(), flags, mode);
    if (fd < 0) {
        return std::unexpected(errno);
    }
    return SafeFD{fd};
}

std::expected<SafeMap, int> read_all(const program_options& options) {
    const std::string& path = options.path_result;
    auto result = open_file(path, O_RDONLY, 0);
    if (!result.has_value()) {
        return std::unexpected(result.error());
    }
    if (options.verbose) {
        std::cerr << "open: se abre el archivo " << path << std::endl;
    }
    off_t length = lseek(result.value().get(), 0, SEEK_END);
    if (length < 0) {
        return std::unexpected(errno);
    }
    size_t size = static_cast<size_t>(length);
    if (options.verbose) {
        std::cerr << "read: se leen " << size << " bytes del archivo de entrada " << path << std::endl;
    }
    void* mem = mmap(NULL, size, PROT_READ, MAP_PRIVATE, result.value().get(), 0);
    if (mem == MAP_FAILED) {
        return std::unexpected(errno);
    }
    SafeMap content(std::string_view(static_cast<char*>(mem), size));
    return content;
}

void Usage() {
    std::cout << "Uso: docserver [-v | --verbose] [-h | --help] ARCHIVO | EJECUTABLE [-p | --port] PUERTO [-b | --base] RUTA" << std::endl;
    std::cout << "Muestra el contenido de ARCHIVO o del EJECUTABLE por la salida estándar del cliente." << std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "  -h, --help        Muestra esta ayuda y termina." << std::endl;
    std::cout << "  -v, --verbose     Modo detallado, muestra acciones realizadas." << std::endl;
    std::cout << "  -p, --port        Direccionamiento de puerto, selecciona un puerto por el usuario." << std::endl;
    std::cout << "  -b, --base        Incluir ruta hasta espcífica hasta un directorio deseado." << std::endl;
}

int send_response(const SafeFD& socket, std::string_view header, std::string_view body, const program_options& options) {
    std::string message = std::string(header) + "\n\n" + std::string(body) + "\n";
    ssize_t bytes_sent = send(socket.get(), message.data(), message.size(), 0);
    if (bytes_sent < 0) {
        return errno;
    }
    if (options.verbose) {
        std::cerr << "send: se envían " << message.size() << " bytes de un mensaje" << std::endl;
    }
    return EXIT_SUCCESS;
}


std::expected<SafeFD, int> make_socket(const program_options& options) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        return std::unexpected(errno);
    }
    if (options.verbose) {
        std::cerr << "socket: creación de un socket" << std::endl;
    }
    sockaddr_in local_address {};
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = htonl(INADDR_ANY);
    local_address.sin_port = htons(options.port_num);
    //local_address.sin_port = htons(static_cast<uint16_t>(std::stoi(getenviroment("DOCSERVER_PORT"))));
    int result = bind(fd, reinterpret_cast<const sockaddr*>(&local_address), sizeof(local_address));
    if (result < 0) {
        return std::unexpected(errno);
    }
    if (options.verbose) {
        std::cerr << "bind: asignación del puerto al socket " << options.port_num << std::endl;
    }
    return SafeFD {fd};
}


int listen_connection(const SafeFD& socket, const program_options& options) {
    int listen_result = listen(socket.get(), 5);
    if (options.verbose) {
        std::cerr << "listen: el socket comienza a escuchar" << std::endl;
    }
    if (listen_result < 0) {
        return errno;
    }
    return EXIT_SUCCESS;
}

std::expected<SafeFD, int> accept_connection(const SafeFD& socket, sockaddr_in& client_addr, const program_options& options) {
    socklen_t source_address_length;
    int fd = accept(socket.get(), reinterpret_cast<sockaddr*>(&client_addr), &source_address_length);
    if (fd < 0) {
        return std::unexpected(errno);
    }
    if (options.verbose) {
        std::cerr << "accept: entrada de la conexión aceptada " << std::endl;
    }
    return SafeFD {fd};
}

std::expected<std::string, int> receive_request(const SafeFD& socket, size_t max_size, const program_options& options) {
    std::string message_text;
    message_text.resize(max_size);
    ssize_t bytes_read = recv(socket.get(), message_text.data(), max_size, 0);
    if (bytes_read < 0) {
        return std::unexpected(errno);
    }
    if (options.verbose) {
        std::cerr << "recive: se ha recibido el mensaje de " << bytes_read << " bytes" << std::endl;
    }
    message_text.resize(static_cast<unsigned int>(bytes_read));
    return message_text;
}

std::expected<std::string, execute_program_error> execute_program(const exec_environment& env, const program_options& options) {
    //std::cerr << "Dentro de execute";
    int access_result = access(options.path_result.c_str(), X_OK);
    //std::cerr << "access";
    if (options.verbose) {
        std::cerr << "access: se compureba el acceso" << std::endl;
    }
    if (access_result != 0) {
        execute_program_error access_error {EXIT_FAILURE, errno};
        return std::unexpected(access_error);
    }
    const size_t buffer_size {4096};
    int pipefd[2];
    int result_pipe = pipe(pipefd);
    if (options.verbose) {
        std::cerr << "pipe: se crea el pipe para usarlo entre el proceso padre e hijo" << std::endl;
    }
    //std::cerr << "pipe";
    if (result_pipe < 0) {
        execute_program_error pipe_error {EXIT_FAILURE, errno};
        return std::unexpected(pipe_error);
    }

    pid_t pid = fork();
    if (options.verbose) {
        std::cerr << "fork: se crea el proceso hijo" << std::endl;
    }
    //std::cerr << "fork";
    if (pid < 0) {
        // Error
        close(pipefd[0]);
        close(pipefd[1]);
        //std::cerr << " Error fork";
        execute_program_error pid_error {EXIT_FAILURE, errno};
        return std::unexpected(pid_error);
    } else
    if (pid == 0) {
        // Hijo
        if (options.verbose) {
            std::cerr << "proceso hijo: se ejecuta el contenido del proceso hijo" << std::endl;
        }
        
        close(pipefd[0]);
        
        int dup_result = dup2(pipefd[1], STDOUT_FILENO);
        if (dup_result < 0) {
            execute_program_error dup_error {EXIT_FAILURE, errno};
            close(pipefd[1]);
            return std::unexpected(dup_error);
        }
        const char* args[] = {options.path_result.c_str(), nullptr};

        std::string SERVER_BASEDIR = "SERVER_BASEDIR=" + env[0];
        std::string REQUEST_PATH = "REQUEST_PATH=" + env[1];
        std::string REMOTE_PORT = "REMOTE_PORT=" + env[2];
        std::string REMOTE_IP = "REMOTE_IP="+ env[3];
        const char* env_data[] = {SERVER_BASEDIR.c_str(), REQUEST_PATH.c_str(), REMOTE_PORT.c_str(), REMOTE_IP.c_str(), nullptr};
        
        if (options.verbose) {
            std::cerr << "execve: ejecución del programa" << std::endl;
        }

        //execve(options.path_result.c_str(), args, env_data);
        execve(options.path_result.c_str(), const_cast<char* const*>(args), const_cast<char* const*>(env_data));
       
        execute_program_error execve_error {EXIT_FAILURE, -15};
        return std::unexpected(execve_error);
        //std::cerr << "execve";
    } else 
    if (pid > 0) {
        // Padre
        int status {};
        close(pipefd[1]);
        int waitpid_result = waitpid(pid, &status, 0);
        if (waitpid_result < 0) {
            execute_program_error waitpid_error {EXIT_FAILURE, errno};
            close(pipefd[0]);
            return std::unexpected(waitpid_error);
        }

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == EXIT_SUCCESS) {
                std::array <char, buffer_size> buffer {};
                bool flag{true};
                std::string listen{};
                while (flag) {
                    ssize_t nbytes = read(pipefd[0], buffer.data(), buffer_size);
                    if (nbytes < 0) {
                        execute_program_error read_error {EXIT_FAILURE, errno};
                        close(pipefd[0]);
                        return std::unexpected(read_error);
                    } else {
                        listen.append(buffer.data(), 0, static_cast<size_t>(nbytes));
                        if (static_cast<size_t>(nbytes) < buffer_size) {
                            flag = false;
                        }
                    }
                }
                close(pipefd[0]);
                return listen;
            } else {
                close(pipefd[0]);
                execute_program_error WEXITSTATUS_error {EXIT_FAILURE, WEXITSTATUS(status)};
                return std::unexpected(WEXITSTATUS_error);
            }
        } else {
            close(pipefd[0]);
            execute_program_error WIFEXITED_error {EXIT_FAILURE, errno};
            return std::unexpected(WIFEXITED_error);
        }
    }
    execute_program_error unknown_error {EXIT_FAILURE, -10};
    return std::unexpected(unknown_error);
}

