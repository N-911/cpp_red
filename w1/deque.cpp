//#include "test_runner.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <deque>

using namespace std;

template <typename T>
class Deque {
public:
//    template< class InputIt >
//    Deque(InputIt first, InputIt last) {
//        f_data = vector<T>(first, last);
//    }

    Deque() = default;

    ~Deque() = default;

    bool Empty() const {
        return f_data.empty() && b_data.empty();
    }

    size_t Size() const {
        return (f_data.size() + b_data.size());
    }

    void Clear() {
        f_data.clear();
        b_data.clear();
    }

    T& operator[](size_t index) {
        return At(index);
    }

    const T& operator[](size_t index) const {
        const T& res = At(index);
        return res;
    }

    T& Front() {
        if (!f_data.empty()) {
            return f_data.back();
        }
        return b_data.front();
    }

    const T& Front() const {
        if (!f_data.empty()) {
            return f_data.back();
        }
        return b_data.front();
    }

    T& Back() {
        if (b_data.empty()) {
            return f_data.front();
        }
        return b_data.back();
    }

    const T& Back() const {
        if (b_data.empty()) {
            return f_data.front();
        }
        return b_data.back();
    }

    void PushFront(const T& value) {
        f_data.push_back(value);
    }

    void PushBack(const T& value) {
        b_data.push_back(value);
    }

    T& At(size_t index) {
        if (!(index < (f_data.size() + b_data.size()))) {
            throw out_of_range("out of range");
        }
        if (index < f_data.size()) {
            return f_data[f_data.size() - 1 - index];
        } else {
            return b_data[index - f_data.size()];
        }
    }

    T& At(size_t index) const {
        if (!(index < (f_data.size() + b_data.size()))) {
            throw out_of_range("out of range");
        }
        if (index < f_data.size()) {
            return f_data[f_data.size() - 1 - index];
        } else {
            return b_data[index - f_data.size()];
        }
    }


private:
    vector<T> f_data;
    vector<T> b_data;
};


int main() {
    {
        Deque<int> deque;
        deque.PushBack(5);
        deque[0] = 2;
        deque.Front() = 1;
        std::cout << deque[0] << endl;
        deque.PushBack(3);
        deque.PushBack(2);
        deque.Back() = 22;
        cout << deque.Back() << endl;
//        cout << deque.Front() << endl;
    }
    {
        cout << "test 2 _______" << '\n';
        Deque<int> d1;
        d1.PushFront(2);
        d1.PushFront(1);
        d1.PushBack(3);
        d1.PushBack(4);
        cout << d1[2] << endl;
        cout << d1.Back() << endl;
        cout << d1.Front() << endl;
    }

    {
        cout << "test 2 answer _______" << '\n';
        deque<int> d2;
        d2.push_front(2);
        d2.push_front(1);
        d2.push_back(3);
        d2.push_back(4);
        cout << d2[2] << endl;
        cout << d2.back() << endl;
        cout << d2.front() << endl;
    }
        return 0;
}


    /*
    {
        deque<char> letters {'o', 'm', 'g', 'w', 't', 'f'};

        if (!letters.empty()) {
            std::cout << "The first character is: " << letters.front() << '\n';
        }
        letters.front() = '9';

        cout << letters.front() << endl;
    }
*/


/*
vector<int> test = {1,2,3};
    Deque<int> dd(test.begin(), test.end());

    cout << dd[1] << endl;
    cout << "Front = " << dd.Front() << endl;
    cout << dd.Empty() << endl;

*/