#include "driver.h"

#include <iostream>
#include <memory>

#include "sort_utils.h"
#include "../util/util.h"

namespace options {
    constexpr int EXIT = 0;
    constexpr int READ = 1;
    constexpr int FIRST_SORT = 2;
    constexpr int LAST_SORT = FIRST_SORT + NUM_ALGOS - 1;
    constexpr int INVALID = -1;
}

void print_menu() {
    std::cout << "======= SORTING ALGORITHMS =======\n";
    std::cout << "(1) Read data from input file\n";
    std::cout << "(2) Sort data using bubble sort\n";
    std::cout << "(3) Sort data using insertion sort\n";
    std::cout << "(4) Sort data using selection sort\n";
    std::cout << "(5) Sort data using heapsort\n";
    std::cout << "(6) Sort data using mergesort\n";
    std::cout << "(7) Sort data using quicksort\n";
    std::cout << "(0) Exit\n";

    std::cout << ">> ";
}

int read_op() {
    int op;
    if (std::cin >> op)
        return op;
    if (std::cin.eof())
        return options::EXIT;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return options::INVALID;
}

inline bool is_sort(int op) {
    return op >= options::FIRST_SORT && op <= options::LAST_SORT;
}

inline const SortingAlgo& algo_for(int op) {
    return ALGORITHMS[(op - options::FIRST_SORT)];
}

void run_interactive() {
    std::unique_ptr<long[]> data(
            new long[constants::MAXSIZE]
    );
    std::size_t len = 0;

    int op = options::INVALID;
    while (op != options::EXIT) {
        print_menu();
        op = read_op();

        if (op == options::EXIT)
            std::cout << "Exiting program...\n";
        else if (op == options::READ) {
            len = load_input(data.get());
            if (len == 0)
                op = options::EXIT;
        } else if (is_sort(op)) {
            if (len == 0)
                std::cout << "No data loaded: choose " << options::READ << " first\n";
            else
                report_results(run_sort(algo_for(op), data.get(), len));
        } else
            std::cout << "Invalud option, please enter an integer from "
                << options::EXIT << " - " << options::LAST_SORT << '\n';
    }
}

std::size_t run_autonomous(SortResult results[]) {
    std::unique_ptr<long[]> data(new long[constants::MAXSIZE]);
    const std::size_t len = load_input(data.get());

    if (len == 0)
        return 0;

    for (std::size_t i = 0; i < NUM_ALGOS; i++) {
        std::cout << "Running " << ALGORITHMS[i].name << "...\n";
        results[i] = run_sort(ALGORITHMS[i], data.get(), len);
    }

    return NUM_ALGOS;
}
