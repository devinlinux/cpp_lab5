#include "efficient.h"

#include <climits>
#include <type_traits>
#include <cstring>
#include "omp.h"
#include "util.h"

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
	if(len<=1){
		return;
	}
	std::size_t mid =len/2;
	mergesort(data,mid);
	mergesort(data+mid,len-mid);
	long* temp=new long[len];
	std::size_t i=0;
	std::size_t j=mid;
	std::size_t k=0;
	while(i<mid &&j<len){
		if(data[i]<=data[j]){
			temp[k++]=data[i++];
		}else{
			temp[k++]=data[j++];
		}
	}
	while (j<len){
		temp[k++]=data[j++];
	}
	for(std::size_t index=0;index<len;index++){
		data[index]=temp[index];
	}
	delete[] temp;
}

void radixsort(long *data, std::size_t len) noexcept {
    if (len <= 1)
        return;

    typedef typename std::make_unsigned<long>::type ULong;

    const int RADIX = 256;
    const int BITS = 8;
    const int PASSES = sizeof(long);

    const int thread_count = omp_get_max_threads();

    long* temp = new long[len];

    std::size_t* histogram = new std::size_t[thread_count * RADIX];
    std::size_t* offsets = new std::size_t[thread_count * RADIX];

    long* src = data;
    long* dst = temp;

    const ULong SIGN_MASK = static_cast<ULong>(1) << (sizeof(long) * CHAR_BIT - 1);

    for (int pass = 0; pass < PASSES; pass++) {
        const int shift = pass * BITS;

        int actual_threads = 1;

        #pragma omp parallel num_threads(thread_count) shared(src, dst, histogram, offsets, actual_threads)
        {
            const int tid = omp_get_thread_num();

            #pragma omp single
            {
                actual_threads = omp_get_num_threads();
            }

            const std::size_t start = len * tid / actual_threads;
            const std::size_t end = len * (tid + 1) / actual_threads;

            std::size_t* hist = histogram + tid * RADIX;
            std::size_t* pos = offsets + tid * RADIX;

            for (int b = 0; b < RADIX; b++)
                hist[b] = 0;

            for (std::size_t i = start; i < end; i++) {
                ULong key = static_cast<ULong>(src[i]) ^ SIGN_MASK;

                unsigned int bucket =
                    static_cast<unsigned int>((key >> shift) & 0xFFUL);

                hist[bucket]++;
            }

            #pragma omp barrier

            #pragma omp single
            {
                std::size_t sum = 0;

                for (int b = 0; b < RADIX; b++) {
                    for (int t = 0; t < actual_threads; t++) {
                        std::size_t index =
                            t * RADIX + b;

                        offsets[index] = sum;
                        sum += histogram[index];
                    }
                }
            }

            for (std::size_t i = start; i < end; ++i) {
                ULong key = static_cast<ULong>(src[i]) ^ SIGN_MASK;
                unsigned int bucket = static_cast<unsigned int>((key >> shift) & 0xFFUL);

                dst[pos[bucket]++] = src[i];
            }
        }

        long* swap = src;
        src = dst;
        dst = swap;
    }

    if (src != data)
        std::memcpy(data, src, len * sizeof(long));

    delete[] temp;
    delete[] histogram;
    delete[] offsets;
}
