#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "staticSequence.h"
#include "SortMethod.h"

extern bool show_trace;

template <typename Key>
void shell_sort(staticSequence<Key>& sequence, const int size, const double alpha) {
	int delta = size;
	while (delta > 1){
		delta = static_cast<int>(delta * alpha);
		delta = std::max(1, delta);
		for (int i = delta; i < size; i++){
			Key x = sequence[i];
			int j = i;
			while ((j >= delta) && (x < sequence[j - delta])){
				sequence[j] = sequence[j - delta];
				j = j - delta;
			}
			sequence[j] = x;
		}
	}
}

template <typename Key>
void shell_sort_trace(staticSequence<Key>& sequence, const int size, const double alpha) {
	int delta = size;
	int it = 1;
	while (delta > 1){
		delta = static_cast<int>(delta * alpha);
		delta = std::max(1, delta);
		for (int i = delta; i < size; i++){
			Key x = sequence[i];
			int j = i;
			while ((j >= delta) && (x < sequence[j - delta])){
				sequence[j] = sequence[j - delta];
				j = j - delta;
			}
			sequence[j] = x;
		}
		std::cout << "it " << it++ << ": " << sequence << std::endl;
	}
}

template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
  ShellSort(const staticSequence<Key>& s, const double alpha) :
    SortMethod<Key>(s), alpha_(alpha) {
    if (alpha < 0 || alpha > 1) throw std::invalid_argument("Parámetro incorrecto, 0 < α < 1");
  }
  void Sort() override {
    if (show_trace) {
			shell_sort_trace<Key>(this->s_, this->s_.get_size(), alpha_);
		} else {
			shell_sort<Key>(this->s_, this->s_.get_size(), alpha_);
		}
  }
 private:
  double alpha_;
};

#endif