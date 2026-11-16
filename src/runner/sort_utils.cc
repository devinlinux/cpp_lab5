#include "sort_utils.h"

//  imports
#include <algorithm>
#include <iostream>
#include <memory>

#include "../util/util.h"

std::size_t load_input(long *data) {
    const std::string path = input_path();
    std::size_t len = read_data(path.c_str(), data);

    if (len == 0)
        std::cerr << "No data read from " << path << '\n';
    else
        std::cout << "Read " << len << " items from " << path << '\n';

    return len;
}

SortResult run_sort(const SortingAlgo& algo, const long* input, std::size_t len) {
    std::unique_ptr<long[]> working_data(new long[len]);
    std::copy(input, input + len, working_data.get());

    const double ms = benchmark([&]() {
            algo.func(working_data.get(), len);
    });

    SortResult result {
        algo.name,
        len,
        ms,
        std::is_sorted(working_data.get(), working_data.get() + len),
        output_path(std::string(algo.tag)),
    };

    write_data(result.output_file.c_str(), working_data.get(), len);
    return result;
}

void report_results(const SortResult& result) {
    std::cout << result.name << " ran for: " << result.ms / 1000.0 << "s\n";
    if (!result.sorted)
        std::cout << "WARNING: output is not sorted\n";
}
