#include "docserver_tools.h"

std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]) {
    std::vector<std::string_view> args(argv + 1, argv + argc);
    program_options options;
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == "-h" || *it == "--help") {
            options.show_help = true;
        } else 
        if (*it == "-v" || *it == "--verbose") {
            options.verbose = true;        
        } else {
            if(it->starts_with("-")) {
                return std::unexpected(parse_args_errors::unknown_option);
            }
            if (!options.output_filename.empty()) {
                return std::unexpected(parse_args_errors::over_files);
            }
            options.output_filename = *it;
        }
    }
    if (options.output_filename.empty()) {
        return std::unexpected(parse_args_errors::missing_argument);
    }
    return options;
}

std::expected<SafeFD, int> open_file(const std::string& path, int flags, mode_t mode = 0) {
    int fd = open(path.c_str(), flags, mode);
    if (fd < 0) {
        return std::unexpected(errno);
    }
    return SafeFD{fd};
}

std::expected<SafeMap, int> read_all(const program_options& options) {
    const std::string& path = options.output_filename;
    auto result = open_file(path, O_RDONLY);
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
    std::cout << "Uso: docserver [-v | --verbose] [-h | --help] ARCHIVO" << std::endl;
    std::cout << "Muestra el contenido de ARCHIVO por la salida estándar." << std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "  -h, --help        Muestra esta ayuda y termina." << std::endl;
    std::cout << "  -v, --verbose     Modo detallado, muestra acciones realizadas." << std::endl;
}

void send_response(std::string_view header, std::string_view body) {
    std::cout << header << std::endl << std::endl;
    if (!body.empty()) {
        std::cout << body << std::endl;
    }
}