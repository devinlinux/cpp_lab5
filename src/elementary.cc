#include "elementary.h"
#include "util.h"

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
    for (std::size_t i = 0; i < len - 1; i++) {
        std::size_t min = i;

        #pragma omp parallel
        {
            std::size_t local_min = i;

            #pragma omp for nowait
            for (std::size_t j = i + 1; j < len; j++) {
                if (data[j] < data[local_min])
                    local_min = j;
            }

            #pragma omp critical
            {
                if (data[local_min] < data[min])
                    min = local_min;
            }
        }

        swap(data[i], data[min]);
    }
}
