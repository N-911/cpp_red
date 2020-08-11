#pragma once

#include <cstdlib>
#include <iterator>
#include <algorithm>
/*
 *  методы Size, Capacity и PushBack
 * - метод Capacity должен возвращать текущую ёмкость вектора — количество элементов,
 * которое помещается в блок памяти, выделенный вектором в данный момент
 * - метод Size должен возвращать количество элементов в векторе
 * - метод PushBack добавляет новый элемент в конец вектора; если в текущем выделенном блоке памяти
 * не осталось свободного места (т.е. Size() == Capacity()),
 * вектор должен выделить блок размера 2 * Capacity(), скопировать в него все элементы и удалить старый.
 *  первый вызов метода PushBack для вновь созданного объекта должен делать ёмкость, равной единице
 * - метод PushBack должен иметь амортизированную константную сложность
 * - методы begin и end должны возвращать итераторы текущие начало и конец вектора
 * - в деструкторе должен освобождаться текущий блок памяти, выделенный вектором
 */

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
    _size = size;
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
  const T* begin() const{
      return data;
  }

  T* end() {
      return _end;
  }

  const T* end() const {
    return _end;
  }

  size_t Size() const {
      return _size;
  }

  size_t Capacity() const {
      return _cap;
}

  void PushBack(const T& value) {
      if (_cap == 0) {
          T* new_data = new T[1];
          _end = new_data + 1;
          ++_cap;
          new_data[0] = value;
          ++_size;
          data = new_data;
      } else if (_size < _cap) {
        *_end++= value;
        ++_size;
      }

      else if (_size == _cap) {
          T* new_data = new T[_cap * 2];
          _cap = _cap * 2;
//          std :: copy(data, _end, new_data);
          for (size_t i = 0; i < _size; ++i) {
              *(new_data + i) = *(data + i);
          }
          _end = new_data + _size;
          *_end++ = value;
//          *(new_data +_size - 1) = value;
          ++_size;
          delete [] data;
          data = new_data;
      }
  }

private:
    T* data;
    T* _end;
    size_t _size;
    size_t _cap;
};

/*

  : data(new T[size])
  , size(size)
  , capacity(size)


template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
  data[size++] = value;
}

 */