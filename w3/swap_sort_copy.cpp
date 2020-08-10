#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

/*
 *  template <typename T> void Swap(T* first, T* second) — обменивает местами значения,
 *  на которые указывают указатели first и second
 */

template <typename T>
void Swap(T* first, T* second) {
    auto temp = *first;
    *first = *second;
    *second = temp;
}

/*
 * template <typename T> void SortPointers(vector<T*>& pointers) — сортирует указатели по значениям,
 * на которые они указывают
 */
template <typename T>
void SortPointers(vector<T*>& pointers) {
    sort(pointers.begin(), pointers.end(), [](const T* val1, const T* val2) {
        return *val1 < *val2 ;});
}

/*
 * template <typename T> void ReversedCopy(T* src, size_t count, T* dst) —
 * копирует в обратном порядке count элементов, начиная с адреса в указателе src,
 * в область памяти, начинающуюся по адресу dst. При этом
    - каждый объект из диапазона [src; src + count) должен быть скопирован не более одного раза;
    - диапазоны [src; src + count) и [dst; dst + count) могут пересекаться;
    - элементы в части диапазона [src; src + count), которая не пересекается с [dst; dst + count),
    должны остаться неизменными.
 */

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
    auto src_begin = source;
    auto src_end = source + count;
    auto dst_begin = destination;
    auto dst_end = destination + count;

    if (dst_begin >= src_end || dst_end <= src_begin) {
        reverse_copy(src_begin, src_end, dst_begin);
    } else if (dst_begin > src_begin) {                 // dst right
        for (size_t i = 0; src_begin + i < dst_begin; ++i) {
            *(dst_end - i - 1) = *(src_begin + i);
        }
        reverse(dst_begin, src_end);
    } else {                                        // dst left
        for (size_t i = 0; src_end - 1 - i >= dst_end; ++i) {
            *(dst_begin + i) = *(src_end - i - 1);
        }
        reverse(src_begin, dst_end);
    }

}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);

  /*
cout << "=src_original=====================" << '\n';
    const size_t count = 7;

    int* src = new int[count];
    int* dst = new int[count];

    for (size_t i = 0; i < count; ++i) {
        src[i] = i + 1;
    }
    for (int i = 0; src + i < (src + count); ++i) {
        cout << src[i] << ' ';
    }
    cout <<'\n';

    ReversedCopy(src, count - 1, src - 3);
//    const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
//    ASSERT_EQUAL(vector<int>(source, source + count), expected2);

    cout << "=src=====================" << '\n';

    for (int i = 0; src + i < (src + count); ++i) {
        cout << src[i] << ' ';
    }
    cout <<'\n';

    cout << "=dst====================" << '\n';

    for (int i = 0;  dst + i < (dst + count); ++i) {
        cout << dst[i] << ' ';
    }
    cout <<'\n';


    delete[] dst;
    delete[] src;
*/

  return 0;
}
