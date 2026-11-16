#include "util.h"

std::string input_path() {
    return std::string(constants::INPUT_DIR) +
        std::string(constants::INPUT_PATH);
}

std::string output_path(std::string algo) {
    std::string path(constants::OUTPUT_DIR);
    return path + std::string(constants::OUTPUT_PREFIX) + algo +
        std::string(constants::OUTPUT_SUFFIX);
}

std::size_t read_data(const char* path, long* data) {
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Failed to open input file");

    std::size_t len = 0;
    while (len < constants::MAXSIZE && file >> data[len]) len++;

    return len;
}

void write_data(const char* path, const long* data, std::size_t len) {
    std::ofstream file(path);
    if (!file)
        throw std::runtime_error("Failed to open output file");

    for (std::size_t i = 0; i < len; i++) {
        if (i != 0)
            file << ' ';
        file << data[i];
    }
}
