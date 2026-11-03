#ifndef STATICSEQUENCE_H
#define STATICSEQUENCE_H

#include "sequence.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

template <class Key> class staticSequence;
template <class Key> std::ostream& operator<<(std::ostream&, const staticSequence<Key>&);
template <class Key> std::istream& operator>>(std::istream&, staticSequence<Key>&);

template <class Key>
class staticSequence : public Sequence<Key> {
 public:
	staticSequence(const unsigned size) : v_(size), counter_(0), size_(size) {
    	if (size_ == 0) throw std::invalid_argument("Tamaño de bloque igual a 0");
  }
	
  bool search(const Key& key) const override {
		return std::find(v_.begin(), v_.end(), key) != v_.end();
	}

  bool insert(const Key& key) override {
		if (isFull()) return false;
		v_[counter_++] = key;
		return true;
	}

  Key& operator[](const int i) override {
  	return v_[i];
	}

  const Key& operator[](const int i) const override {
  	return v_[i];
	}

  void swap(const unsigned i, const unsigned j) {
  	std::swap(v_[i], v_[j]);
	}

  bool isFull() const {
  	return counter_ == size_;
	}

  unsigned get_size() const {
  	return size_;
	}

  friend std::ostream& operator<< <>(std::ostream&, const staticSequence<Key>&);
  friend std::istream& operator>> <>(std::istream&, staticSequence<Key>&);

 private:
  std::vector<Key> v_;
  unsigned counter_;
  unsigned size_;
};

template <class Key>
std::ostream& operator<<(std::ostream& os, const staticSequence<Key>& sequence) {
  for (size_t i = 0; i < sequence.size_; i++) {
    os << sequence[i] << ' ';
  }
  return os;
}

template <class Key>
std::istream& operator>>(std::istream& is, staticSequence<Key>& sequence) {
  Key tmp;
  sequence.v_.clear();
  for (unsigned i = 0; i < sequence.size_; i++) {
    is >> tmp;
    sequence.v_.push_back(tmp);
  }
  sequence.counter_ = 0;
  return is;
}

#endif