#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if ((range_end - range_begin) < 2) {
        return;
    }
    vector <typename RandomIt :: value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    RandomIt it_one = elements.begin() + elements.size() / 3;
    RandomIt it_two = elements.begin() + elements.size() * 2 / 3;

    MergeSort(elements.begin(), it_one);
    MergeSort(it_one, it_two);
    MergeSort(it_two, elements.end());
    vector<typename RandomIt::value_type> elements_temp;

    merge(make_move_iterator(elements.begin()), make_move_iterator(it_one), make_move_iterator(it_one), make_move_iterator(it_two), back_inserter(elements_temp));

    merge( make_move_iterator(elements_temp.begin()), make_move_iterator(elements_temp.end()), make_move_iterator(it_two), make_move_iterator(elements.end()), range_begin);

}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
