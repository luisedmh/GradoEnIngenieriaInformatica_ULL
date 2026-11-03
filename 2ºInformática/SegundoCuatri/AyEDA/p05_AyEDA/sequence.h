#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

template <class Key>
class Sequence {
 public:
  virtual ~Sequence() {}
  virtual bool search(const Key& key) const = 0;
  virtual bool insert(const Key& key) = 0;
  virtual Key& operator[](const int) = 0;
  virtual const Key& operator[](const int) const = 0;
};

#endif