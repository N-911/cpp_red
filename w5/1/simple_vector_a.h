#pragma once

#include <algorithm>


using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    explicit SimpleVector(const SimpleVector& other);
    ~SimpleVector();

    void operator=(const SimpleVector& rhs);
    T& operator[](size_t index);


    T* begin() const;
    T* end() const;


    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};


template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
        : data(new T[size])
        , size(size)
        , capacity(size)
{
}

template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector& other) :
        data(new T [other.capacity]), size(other.size), capacity(other.capacity) {
    copy (other.begin(), other.end(), data);
}


template <typename T>
void SimpleVector<T>::operator=(const SimpleVector& rhs) {
    if (rhs.size <= capacity) {
        // У нас достаточно памяти - просто копируем элементы
        copy(rhs.begin(), rhs.end(), begin());
        size = rhs.size;
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
        swap(tmp.size, size);
        swap(tmp.capacity, capacity);
    }
}


template <typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
size_t SimpleVector<T>::Size() const {
    return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity;
}

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


template <typename T>
T* SimpleVector<T>::begin() const {
    return data;
}

template <typename T>
T* SimpleVector<T>::end() const {
    return data + size;
}


