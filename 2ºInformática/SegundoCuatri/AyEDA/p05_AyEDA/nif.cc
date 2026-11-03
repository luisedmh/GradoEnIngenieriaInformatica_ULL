#include "nif.h"

bool nif::operator<(const nif& other) const {
  return value_ < other.value_;
}

bool nif::operator>(const nif& other) const {
  return value_ > other.value_;
}

bool nif::operator==(const nif& other) const {
  return value_ == other.value_;
}

bool nif::operator!=(const nif& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const nif& n) {
	os << n.value_;
	return os;
}

std::istream& operator>>(std::istream& is, nif& n) {
	long aux;
	is >> aux;
	n = nif(aux);
	return is;
}