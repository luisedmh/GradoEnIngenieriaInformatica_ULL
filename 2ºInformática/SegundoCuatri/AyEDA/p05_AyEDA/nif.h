#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <cstdlib>

class nif {
 public:
  explicit nif(long val = 10000000 + rand() % 90000000) : value_(val) {}

  operator long() const { return value_; };

  bool operator<(const nif& other) const;
  bool operator>(const nif& other) const;
  bool operator==(const nif& other) const;
  bool operator!=(const nif& other) const;
  
  friend std::ostream& operator<<(std::ostream& os, const nif& n);
  friend std::istream& operator>>(std::istream& is, nif& n);

 private:
  long value_;
};



#endif