#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "staticSequence.h"
#include "SortMethod.h"

extern bool show_trace;

template <typename Key>
void down(int i, staticSequence<Key>& sequence, const int size) {
	while (2 * i <= size) {
		int h, h1 = 2 * i, h2 = h1 + 1;
		if (h1 == size) h = h1;
		else if (sequence[h1] > sequence[h2]) h = h1;
		else h = h2;
		if (sequence[h] <= sequence[i]) break;
		else {
			sequence.swap(i, h);
			i = h;
		}
	}
}

template <typename Key>
void heap_sort(staticSequence<Key>& sequence, const int size) {
	for (int i = size / 2; i >= 0; i--) {
		down(i, sequence, size);
	}
	for (int i = size - 1; i > 0; i--) {
		sequence.swap(0, i);
		down(0, sequence, i - 1);
	}
}

template <typename Key>
void heap_sort_trace(staticSequence<Key>& sequence, const int size) {
	int it = 1;
	for (int i = size / 2; i >= 0; i--) {
		down(i, sequence, size);
		std::cout << "it " << it++ << ": " << sequence << std::endl;
	}
	for (int i = size - 1; i > 0; i--) {
		sequence.swap(0, i);
		down(0, sequence, i - 1);
		std::cout << "it " << it++ << ": " << sequence << std::endl;
	}
}

template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
  explicit HeapSort(const staticSequence<Key>& s) : SortMethod<Key>(s) {}
  void Sort() override {
    if (show_trace) {
			heap_sort_trace<Key>(this->s_, this->s_.get_size());
		} else {
			heap_sort<Key>(this->s_, this->s_.get_size());
		}
  }
};

#endif