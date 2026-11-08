#ifndef UTIL_H_
#define UTIL_H_

//  imports
#include <fstream>

inline void swap(long& a, long& b) noexcept {
    long temp = a;
    a = b;
    b = temp;
}

std::size_t read_data(const char* path, long* data) {
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Failed to open input file");

    std::size_t len = 0;
    while (file >> data[len]) len++;

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

#endif  //  UTIL_H_
