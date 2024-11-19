#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstddef>

class Element {
public:
  std::size_t &index() { return index_; }

private:
  std::size_t index_ = 0;
};

#endif