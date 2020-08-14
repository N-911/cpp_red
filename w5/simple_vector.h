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


using namespace std;

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

    explicit SimpleVector (const SimpleVector& other) :
            data(new T [other._cap]), _size(other._size), _cap(other._cap) {
        copy (other.begin(), other.end(), data);
    }

    void operator=(const SimpleVector& rhs) {
        if (rhs._size <= _cap) {
            // У нас достаточно памяти - просто копируем элементы
            copy(rhs.begin(), rhs.end(), begin());
            _size = rhs._size;
        } else {
            // Это так называемая идиома copy-and-swap.
            // Мы создаём временный вектор с помощью
            // конструктора копирования, а затем обмениваем его поля со своими.
            // Так мы достигаем двух целей:
            //  - избегаем дублирования кода в конструкторе копирования
            //    и операторе присваивания
            //  - обеспечиваем согласованное поведение конструктора копирования
            //    и оператора присваивания
            SimpleVector<T> tmp(rhs);
            swap(tmp.data, data);
            swap(tmp._size, _size);
            swap(tmp._cap, _cap);
        }
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