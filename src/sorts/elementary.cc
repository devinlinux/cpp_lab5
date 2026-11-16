#include "elementary.h"
#include "../util/util.h"

void bubble_sort(long *data, std::size_t len) noexcept {
    if (len < 2) return;

    for (std::size_t i = 0; i < len - 1; i++){
        for (std::size_t j = len - 1; j > i; --j){
            if (data[j] <  data[j - 1]){
                swap(data[j], data[j-1]);
            }
        }
    }
}

void insertion_sort(long *data, std::size_t len) noexcept {
    for (std::size_t i = 1; i < len; i++) {
        const long key = data[i];

        std::size_t j = i;
        while (j > 0 && data[j - 1] > key) {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = key;
    }
}

void selection_sort(long *data, std::size_t len) noexcept {
    if (len < 2) return;

    for (std::size_t i = 0; i < len - 1; i++) {
        std::size_t min = i;
        for (std::size_t j = i + 1; j < len; j++) {
            if (data[j] < data[min])
                min = j;
        }

        if (min != i)
            swap(data[i], data[min]);
    }
}
