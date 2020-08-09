#pragma once

#include <cstdlib>
//#include <iterator>

template <typename T>
class SimpleVector {
public:
  SimpleVector() {
      data = nullptr;
      _end = nullptr;
      _cap = 0;
  }

  explicit SimpleVector(size_t size) {
    data = new T[size];
    _end = data + size;
      _cap = size;
  }
  ~SimpleVector() {
      delete [] data;
  }

  T& operator[](size_t index) {
      return data[index];
  }

  T* begin() {
      return data;
  }
  T* end() {
      return _end;
  }

  size_t Size() const {
//      return distance(data, _end);
      return _end - data;
//      return 0;
  }
  size_t Capacity() const {
      return _cap;
  }

  void PushBack(const T& value) {
      if (_cap == 0) {
          data = new T[1];
          _end = data + 1;
          ++_size;
          ++_cap;
          data[_size - 1] = value;
      }


  }

private:
    T* data;
    T* _end;
    size_t _size;
    size_t _cap;
};

