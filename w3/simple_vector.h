#pragma once

#include <cstdlib>
#include <iterator>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
  SimpleVector() {
      data = nullptr;
      _end = nullptr;
      _cap = 0;
      _size = 0;
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
      if (_cap == 0 && _size == 0) {
          T* new_data = new T[1];
          T* new_end = new_data + 1;
          ++_cap;

          new_data[_size] = value;
          ++_size;
          data = new_data;
          _end = new_end;

      } else if (_size < _cap) {
        data[_size] =  value;
      }

      else if (_size == _cap) {
          T* new_data = new T[_cap * 2];
          T* new_end = new_data + (_cap * 2);
          _cap = _cap * 2;

          for (size_t i = 0; data + i < _end; ++i) {
              *(new_data + i) = *(data);
          }

          data = new_data;
          _end = new_end;
          *(data + _size) = value;
          ++_size;
//          copy(data, _end, new_data);
      }
  }

private:
    T* data;
    T* _end;
    size_t _size;
    size_t _cap;
};

