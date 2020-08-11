#include <vector>
#include <tuple>
#include <iostream>
#include <array>

#include "test_runner.h"
#include "profile.h"
using namespace std;

// Прокрутите код, чтобы увидеть полностью на мобильных устройствах
vector<int> BuildVector(int i) {
    return {i, i + 1, i + 2, i + 3, i + 4};
}

tuple<int, int, int, int, int> BuildTuple(int i) {
    return make_tuple(i, i + 1, i + 2, i + 3, i + 4);
}

array<int, 5> BuildArray(int i) {
    return {i, i + 1, i + 2, i + 3, i + 4};
}

const int COUNT = 1000000;

int main() {
    // Используем данную переменную, чтобы при оптимизации не удалился код,
    // связанный с тестированием
    size_t tmp = 0;

    {
        LOG_DURATION("vector");

        for (int i = 0; i < COUNT; ++i) { // C * N
            auto numbers = BuildVector(i);
            tmp += numbers.size();
        }
    }

    {
        LOG_DURATION("tuple");

        for (int i = 0; i < COUNT; ++i) { // C * N
            auto numbers = BuildTuple(i);
            tmp += std::get<0>(numbers);
        }
    }

    {
        LOG_DURATION("array");

        for (int i = 0; i < COUNT; ++i) { // C * N * logN
            auto numbers = BuildArray(i);
            sort(begin(numbers), end(numbers));
            tmp += numbers.size();
        }
    }

    cout << tmp;

    return 0;
}//
// Created by Serhiy Nikolayenko on 8/11/20.
//

