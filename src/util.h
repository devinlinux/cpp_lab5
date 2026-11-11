#ifndef UTIL_H_
#define UTIL_H_

//  imports
#include <string_view>
#include <fstream>
#include <chrono>

namespace constants {
    constexpr std::string_view INPUT_PATH = "lab5_input.txt";
    constexpr std::string_view OUTPUT_PATH = "lab5_output_";

    constexpr size_t MAXSIZE = 500;
}

inline void swap(long& a, long& b) noexcept {
    long temp = a;
    a = b;
    b = temp;
}

[[nodiscard]] std::size_t read_data(const char* path, long* data);

void write_data(const char* path, const long* data, std::size_t len);

template <typename Func>
[[nodiscard]] double benchmark(Func&& func) noexcept {
    auto start = std::chrono::steady_clock::now();

    func();

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

#endif  //  UTIL_H_
