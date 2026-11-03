#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "staticSequence.h"
#include "SortMethod.h"

extern bool show_trace;

template <typename Key>
void quick_sort(staticSequence<Key>& sequence, const int start, const int end) {
	int i = start;
	int f = end;
	int p = sequence[(i + f) / 2];
	while (i <= f) {
		while (sequence[i] < p) i++;
		while (sequence[f] > p) f--;
		if (i <= f) {
		sequence.swap(i, f);
		i++;
		f--;
		}
	}
	if (start < f) quick_sort(sequence, start, f);
	if (i < end) quick_sort(sequence, i, end);
}

template <typename Key>
void quick_sort_trace(staticSequence<Key>& sequence, const int start, const int end, int& it) {
	int i = start;
	int f = end;
	int p = sequence[(i + f) / 2];
	while (i <= f) {
		while (sequence[i] < p) i++;
		while (sequence[f] > p) f--;
		if (i <= f) {
			sequence.swap(i, f);
			i++;
			f--;
		}
	}
	std::cout << "it " << it++ << ": " << sequence << std::endl;
	if (start < f) quick_sort_trace(sequence, start, f, it);
	if (i < end) quick_sort_trace(sequence, i, end, it);
}

template <class Key>
class QuickSort : public SortMethod<Key> {
 public:
  explicit QuickSort(const staticSequence<Key>& s) : SortMethod<Key>(s), it_(1) {}
  void Sort() override {
    if (show_trace) {
			quick_sort_trace<Key>(this->s_, 0, this->s_.get_size() - 1, it_);
		} else {
			quick_sort<Key>(this->s_, 0, this->s_.get_size() - 1);
		}
  }
 private:
  int it_;
};

#endif