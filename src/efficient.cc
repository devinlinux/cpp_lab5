#include "efficient.h"

#include <cstring>
#include "util.h"

//  function prototypes
std::size_t partition(long* data, std::size_t len) noexcept;

void heapsort(long *data, std::size_t len) noexcept {
	if(len<=1){
		return;
	}

	for(std::size_t i = len / 2; i > 0; --i){
		std::size_t first = i -1;
		std::size_t largest = 2* first +1;
		while (largest <= len -1){
			if (largest < len - 1 && data[largest] < data[largest +1])
				largest++;

			if (data[first] < data[largest]){
				swap(data[first], data[largest]);
				first = largest;
				largest = 2* first + 1;
			}

			else
				break;
		}
	}

	for (std::size_t i = len - 1; i >= 1; --i){
		swap(data[0], data[i]);

		std::size_t first = 0;
		std::size_t largest = 1;
		while (largest <= i -1){
			if (largest < i -1 && data[largest] < data[largest + 1])
				largest++;
			if (data[first] < data[largest]){
				swap(data[first], data[largest]);
				first = largest;
				largest = 2 * first + 1;

			}
			else
				break;
		}

	}

}

void mergesort(long *data, std::size_t len) noexcept {
    if (len <= 1) return;

    const std::size_t mid = len / 2;
    mergesort(data, mid);
    mergesort(data + mid, len - mid);

    long* temp = new long[len];
    std::size_t i = 0;
    std::size_t j = mid;
    std::size_t k = 0;

    while (i < mid && j < len) {
        if (data[i] <= data[j])
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while (i < mid) temp[k++] = data[i++];
    while (j < len) temp[k++] = data[j++];

    for (std::size_t idx = 0; idx < len; idx++)
        data[idx] = temp[idx];

    delete[] temp;
}

void quicksort(long *data, std::size_t len) noexcept {
    while (len > 1) {
        const std::size_t split = partition(data, len);
        if (split < len - split) {
            quicksort(data, split);
            data += split;
            len -= split;
        } else {
            quicksort(data + split, len - split);
            len = split;
        }
    }
}

std::size_t partition(long *data, std::size_t len) noexcept {
    const std::size_t last = len - 1;
    const std::size_t mid = last / 2;

    if (data[mid] < data[0]) swap(data[mid], data[0]);
    if (data[last] < data[0]) swap(data[last], data[0]);
    if (data[last] < data[mid]) swap(data[last], data[mid]);

    const long pivot = data[mid];
    std::size_t i = 0;
    std::size_t j = last;

    while (true) {
        while (data[i] < pivot) i++;
        while (pivot < data[j]) j--;

        if (i >= j) return j + 1;

        swap(data[i], data[j]);
        i++;
        j--;
    }
}
