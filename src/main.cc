//  imports
#include <iostream>
#include <iomanip>

#include "runner/driver.h"

//  function prototypes
bool is_auto_flag(std::string_view arg);
void bulk_report(const SortResult results[], std::size_t len);

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            run_interactive();
        } else if (is_auto_flag(argv[1])) {
            SortResult results[NUM_ALGOS];
            const std::size_t len = run_autonomous(results);
            bulk_report(results, len);
        } else {
            std::cerr << "Unknown option: " << argv[1] <<
                " run with no arguments for interactive mode, or -a / --auto\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//  simple clap
bool is_auto_flag(std::string_view arg) {
    return arg == "-a" || arg == "--auto";
}

void bulk_report(const SortResult results[], std::size_t len) {
    if (len == 0) {
        std::cout << "No results to report\n";
        return;
    }

    std::cout << "\n=========== TIMING REPORT ===========\n"
        << "Items sorted: " << results[0].len << "\n\n"
        << std::left  << std::setw(16) << "Algorithm"
        << std::right << std::setw(14) << "Time (s)"
        << std::setw(10) << "Sorted"
        << "  Output\n"
        << std::string(70, '-') << '\n';

    std::cout << std::fixed << std::setprecision(6);
    for (std::size_t i = 0; i < len; i++) {
        const SortResult& r = results[i];
        std::cout << std::left  << std::setw(16) << r.name
            << std::right << std::setw(14) << r.ms / 1000.0
            << std::setw(10) << (r.sorted ? "yes" : "NO")
            << "  " << r.output_file << '\n';
    }
}
