#ifndef INSERTION_H
#define INSERTION_H

#include "staticSequence.h"
#include "SortMethod.h"

extern bool show_trace;

template <typename Key>
void insertion(staticSequence<Key>& sequence, const int size) {
	for (int i = 1; i < size; i++) {
		Key x = sequence[i];
		int j = i - 1;
		while (j >= 0 && x < sequence[j]) {
			sequence[j + 1] = sequence[j];
			j--;
		}
		sequence[j + 1] = x;
	}
}

template <typename Key>
void insertion_trace(staticSequence<Key>& sequence, const int size) {
	int it = 1;
	for (int i = 1; i < size; i++) {
		Key x = sequence[i];
		int j = i - 1;
		while (j >= 0 && x < sequence[j]) {
			sequence[j + 1] = sequence[j];
			j--;
		}
		sequence[j + 1] = x;
		std::cout << "it " << it++ << ": " << sequence << std::endl;
  }
}

template <class Key>
class Insertion : public SortMethod<Key> {
 public:
  explicit Insertion(const staticSequence<Key>& s) : SortMethod<Key>(s) {}
  void Sort() override {
    if (show_trace) {
			insertion_trace<Key>(this->s_, this->s_.get_size());
		} else {
			insertion<Key>(this->s_, this->s_.get_size());
		}  
  }
};

#endif