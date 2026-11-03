#ifndef SHAKESORT_H
#define SHAKESORT_H

#include "staticSequence.h"
#include "SortMethod.h"

extern bool show_trace;

template <typename Key>
void shake_sort(staticSequence<Key>& sequence, const int size) {
	int start = 1;
	int end = size - 1;
	int cam = size;
	while (start < end) {
		for (int j = end; j >= start; j--) {
			if (sequence[j] < sequence[j - 1]) {
				sequence.swap(j - 1, j);
				cam = j;
			}
		}
		start = cam + 1;
		for (int j = start; j <= end; j++) {
			if (sequence[j] < sequence[j - 1]) {
				sequence.swap(j - 1, j);
				cam = j;
			}
		}
		end = cam - 1;
	}
}

template <typename Key>
void shake_sort_trace(staticSequence<Key>& sequence, const int size) {
	int start = 1;
	int end = size - 1;
	int cam = size;
	int it = 1;
	while (start < end) {
		for (int j = end; j >= start; j--) {
			if (sequence[j] < sequence[j - 1]) {
				sequence.swap(j - 1, j);
				cam = j;
			}
		}
		start = cam + 1;
		for (int j = start; j <= end; j++) {
			if (sequence[j] < sequence[j - 1]) {
				sequence.swap(j - 1, j);
				cam = j;
			}
		}
		end = cam - 1;
		std::cout << "it " << it++ << ": " << sequence << std::endl;
	}
}

template <class Key>
class ShakeSort : public SortMethod<Key> {
 public:
  explicit ShakeSort(const staticSequence<Key>& s) : SortMethod<Key>(s) {}
  void Sort() override {
    if (show_trace) {
			shake_sort_trace<Key>(this->s_, this->s_.get_size());
		} else {
    	shake_sort<Key>(this->s_, this->s_.get_size());			
		}
  }
};

#endif