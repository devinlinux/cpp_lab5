//  imports
#include <iostream>
#include <memory>

#include "util.h"
#include "elementary.h"
#include "efficient.h"

int main() {

    std::unique_ptr<long[]> data(
            new long[constants::MAXSIZE]
    );
    std::size_t len = 0;

    int op = -1;
    while (op != 0) {
        std::cout << "======= SORTING ALGORITHMS =======\n";
        std::cout << "(1) Read data from input file\n";
        std::cout << "(2) Sort data using bubble sort\n";
        std::cout << "(3) Sort data using insertion sort\n";
        std::cout << "(4) Sort data using selection sort\n";
        std::cout << "(7) Sort data using heapsort\n";
        std::cout << "(5) Sort data using mergesort\n";
        std::cout << "(6) Sort data using quicksort\n";
        std::cout << "(0) Exit\n";

        std::cout << ">> ";

        std::cin >> op;

        switch (op) {
            case 0: {
                std::cout << "Exiting program...\n";
                break;
            }
            case 1: {
                len = read_data(constants::INPUT_PATH.data(), data.get());
                if (len <= 0) {
                    std::cerr << "No data read from file\n";
                    op = 0;
                } else
                    std::cout << "Read " << len << " items from the file\n";
                break;
            }
            case 2: {
                double time = benchmark([&]() {
                    bubble_sort(data.get(), len);
                });

                std::cout << "Bubble sort ran for: " << time / 1000.0 << "s\n";
                write_data((std::string(constants::OUTPUT_PATH) + "BUBBLE").c_str(),
                        data.get(), len);
                break;
            }
            case 3: {
                double time = benchmark([&]() {
                    insertion_sort(data.get(), len);
                });

                std::cout << "Insertion sort ran for: " << time / 1000.0 << "s\n";
                write_data((std::string(constants::OUTPUT_PATH) + "INSERTION").c_str(),
                        data.get(), len);
                break;
            }
            case 4: {
                double time = benchmark([&]() {
                    selection_sort(data.get(), len);
                });

                std::cout << "Selection sort ran for: " << time / 1000.0 << "s\n";
                write_data((std::string(constants::OUTPUT_PATH) + "SELECTION").c_str(),
                        data.get(), len);
                break;
            }
            case 5: {
                double time = benchmark([&]() {
                    heapsort(data.get(), len);
                });

                std::cout << "Heapsort ran for: " << time / 1000.0 << "s\n";
                write_data((std::string(constants::OUTPUT_PATH) + "HEAP").c_str(),
                        data.get(), len);
                break;
            }
            case 6: {
                double time = benchmark([&]() {
                    mergesort(data.get(), len);
                });

                std::cout << "Mergesort ran for: " << time / 1000.0 << "s\n";
                write_data((std::string(constants::OUTPUT_PATH) + "MERGE").c_str(),
                        data.get(), len);
                break;
            }
            case 7: {
                double time = benchmark([&]() {
                    quicksort(data.get(), len);
                });

                std::cout << "Quicksort ran for: " << time / 1000.0 << "s\n";
                write_data((std::string(constants::OUTPUT_PATH) + "QUICK").c_str(),
                        data.get(), len);
                break;
            }
            default: {
                std::cout << "Invalid option, please enter an integer from 0-7\n";
                break;
            }
        }
    }

    return 0;
}
