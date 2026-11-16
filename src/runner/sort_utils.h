#ifndef SORT_UTILS_
#define SORT_UTILS_

#include <array>
#include <string>

#include "../sorts/elementary.h"
#include "../sorts/efficient.h"

using SortingFunc = void(*)(long[], std::size_t) noexcept;

struct SortingAlgo {
    std::string_view name;
    std::string_view tag;
    SortingFunc func;
};

inline constexpr std::array<SortingAlgo, 6> ALGORITHMS {{
    { "Bubble Sort", "BUBBLE", bubble_sort },
    { "Insertion Sort", "INSERTION", insertion_sort },
    { "Selection Sort", "SELECTION", selection_sort },
    { "Heapsort", "HEAP", heapsort },
    { "Mergesort", "MERGE", mergesort },
    { "Quicksort", "QUICK", quicksort },
}};

inline constexpr std::size_t NUM_ALGOS = ALGORITHMS.size();

struct SortResult {
    std::string_view name;
    std::size_t len;
    double ms;
    bool sorted;
    std::string output_file;
};

[[nodiscard]] std::size_t load_input(long* data);

[[nodiscard]] SortResult run_sort(const SortingAlgo& algo, const long* input, std::size_t len);

void report_results(const SortResult& result);

#endif  //  SORT_UTILS_
