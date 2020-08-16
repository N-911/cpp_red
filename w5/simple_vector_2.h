#include <cstdint>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector()
            {
        data = nullptr;
        _cap = 0;
        _size = 0;
    }

    explicit SimpleVector(size_t size) {
        data = new T[size];
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

    T* end() {
        return data + _size;
    }

    size_t Size() const {
        return _size;
    }

    size_t Capacity() const {
        return _cap;
    }

    void PushBack(T value) {
        if (_cap == 0) {
            T* new_data = new T[1];
            ++_cap;
            data = new_data;
            data[_size++] = move(value);
        } else if (_size < _cap) {
            data[_size++] = move(value);
        }
        else if (_size == _cap) {
            T* new_data = new T[_cap * 2];
            _cap = _cap * 2;
            move(begin(), end(), new_data);
            delete [] data;
            data = new_data;
            data[_size++] = move(value);
        }
    }

private:
    T* data;
    size_t _size;
    size_t _cap;
};


//    explicit SimpleVector (const SimpleVector& other) :
//            data(new T [other._cap]), _size(other._size), _cap(other._cap) {
//        copy (other.begin(), other.end(), data);
//    }


/*
    void operator=(const SimpleVector& rhs) {
        if (rhs._size <= _cap) {
            // У нас достаточно памяти - просто копируем элементы
            move(rhs.begin(), rhs.end(), begin());
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
*/
