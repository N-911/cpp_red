# include "profile.h"

#include <iostream>
#include <set>
#include <vector>
#include <random>

/*
 * auto start = steady_clock::now();
 * auto finish = steady_clock::now();
 * auto duration = finish − start;
 * cout << duration_cast<milliseconds>(duration).count()
 */

using namespace std;


set<int> SelectPositiveNumbers_1(const set<int>& numbers) {
    set<int> subset;
    for (auto it = rbegin(numbers);
         it != rend(numbers) && *it > 0;
         ++it) {
        subset.insert(*it);
    }
    return subset;
}

set<int> SelectPositiveNumbers_2(const set<int>& numbers) {
    const auto subset_begin =
            upper_bound(begin(numbers), end(numbers), 0);
    return set<int>(subset_begin, end(numbers));
}


set<int> SelectPositiveNumbers_3(const set<int>& numbers) {
    const auto subset_begin = numbers.upper_bound(0);
    return set<int>(subset_begin, end(numbers));
}


set<int> SelectPositiveNumbers_4(const set<int>& numbers) {
    set<int> subset;
    const auto subset_begin = numbers.upper_bound(0);
    subset.insert(subset_begin, end(numbers));
    return subset;
}

set<int> SelectPositiveNumbers_5(const set<int>& numbers) {
    set<int> subset;
    for (int number : numbers) {
        if (number > 0) {
            subset.insert(number);
        }
    }
    return subset;
}


int main() {
    set<int> numbers;
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом

    int rand_number;
    for (size_t i = 0; i < 1'000'00; ++i) {
    rand_number = mersenne();
    numbers.insert(rand_number);
    /*
    rand_number = rand();
    if (rand_number > 1'000'000'000) {
            numbers.insert(rand_number);
        } else {
            numbers.insert(-rand_number);
        }
        */
}

    {
        LOG_DURATION("SelectPositiveNumbers_1")
        set<int> res = SelectPositiveNumbers_1(numbers);
    }
    {
        LOG_DURATION("SelectPositiveNumbers_2")
        set<int> res = SelectPositiveNumbers_1(numbers);
    }
    {
        LOG_DURATION("SelectPositiveNumbers_3")
        set<int> res = SelectPositiveNumbers_1(numbers);
    }
    {
        LOG_DURATION("SelectPositiveNumbers_4")
        set<int> res = SelectPositiveNumbers_1(numbers);
    }
    {
        LOG_DURATION("SelectPositiveNumbers_5")
        set<int> res = SelectPositiveNumbers_1(numbers);
    }

    return 0;
}

/*
 * vector<string> all_strings = ReadStrings();
vector<string> strings_to_find = ReadStrings();
auto result = search(begin(all_strings), end(all_strings),
                     begin(strings_to_find), end(strings_to_find));

_________________________________________

 vector<string> strings = ReadStrings();
set<string> chosen_strings;
remove_copy_if(begin(strings), end(strings), inserter(chosen_strings),
               [](const string& s) { return s[0] == 'C'; });


vector<string> strings = ReadStrings();
string joined_string =
    accumulate(begin(strings), end(strings), string());


______________________________________________________________

 set<int> SelectPositiveNumbers(const set<int>& numbers) {
  set<int> subset;
  for (int number : numbers) {
    if (number > 0) {
      subset.insert(number);
    }
  }
  return subset;
}

 */