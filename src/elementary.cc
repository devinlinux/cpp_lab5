#include "elementary.h"

void bubble_sort(long *data, std::size_t len) noexcept {
	if (len < 2) return;

		for (std::size_t i = 0; i < len - 1; i++){
			for (std::size_t j = len - 1; j > i; --j){
				if (data[j] <  data[j - 1]){
					long tmp = data[j];
					data[j] = data[j - 1];
					data[j - 1] = tmp;
				}
			}
		}
	}

void insertion_sort(long *data, std::size_t len) noexcept {
}

void selection_sort(long *data, std::size_t len) noexcept {
}
