#ifndef SORTMETHOD_H
#define SORTMETHOD_H

#include <exception>

#include "staticSequence.h"

template <class Key>
class SortMethod {
 public:
  virtual ~SortMethod() {}
  virtual void Sort() = 0;
  virtual staticSequence<Key> get_sequence() const { return s_; };
  explicit SortMethod(const staticSequence<Key>& s) : s_(s) {}

 protected:
  staticSequence<Key> s_; 
};


#endif