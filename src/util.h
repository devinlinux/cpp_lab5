#ifndef UTIL_H_
#define UTIL_H_

//  imports
#include <string_view>
#include <fstream>
#include <chrono>

namespace constants {
    constexpr std::string_view INPUT_DIR = "res/in/";
    constexpr std::string_view OUTPUT_DIR = "res/out/";

    constexpr std::string_view INPUT_PATH = "lab5_input.txt";

    //  proper formatting for output files is lab5_NAME_out.txt
    constexpr std::string_view OUTPUT_PREFIX = "lab5_";
    constexpr std::string_view OUTPUT_SUFFIX = "_out.txt";

    constexpr size_t MAXSIZE = 500;
}

inline void swap(long& a, long& b) noexcept {
    long temp = a;
    a = b;
    b = temp;
}

//  getter to return the input path
[[nodiscard]] std::string input_path();

//  getter to return the output path
[[nodiscard]] std::string output_path(std::string algo);

//  helper function to read in data upto MAXSIZE
[[nodiscard]] std::size_t read_data(const char* path, long* data);

//  helper function to write the sorted data to the given output file
void write_data(const char* path, const long* data, std::size_t len);

//  returns the elapsed runtime of func() in milliseconds
template <typename Func>
[[nodiscard]] double benchmark(Func&& func) noexcept {
    auto start = std::chrono::steady_clock::now();

    func();

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

#endif  //  UTIL_H_
