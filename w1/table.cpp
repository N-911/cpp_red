#include "test_runner.h"

#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Table {
public:
    Table(size_t row, size_t col) {
        Resize(row, col);
    }

    void Resize(size_t new_row, size_t new_col) {
        if (new_col < 0 || new_row < 0) {
            throw out_of_range("number is negative");
        }
        if (new_row == 0 || new_col == 0) {
            num_rows = 0;
            num_cols = 0;
        }
        else {
            num_rows = new_row;
            num_cols = new_col;
        }
        _table.resize(new_row);
        for (auto& item : _table) {
            item.resize(new_col);
        }
    }

    pair<size_t, size_t> Size() const {
        return {num_rows, num_cols};
    }

    const vector<T>& operator [] (const size_t& index ) const {
       return _table[index];
    }

    vector<T>& operator [] (size_t index ) {
        return _table[index];
    }

private:
    size_t num_rows;
    size_t num_cols;
    vector<vector<T>> _table;
};



void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;

  ASSERT_EQUAL(t[0][0], 42);

  t.Resize(3, 4);
  ASSERT_EQUAL(t[0][0], 42);
    t[1][1] = 11;
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
  t.Resize(2,2);
  ASSERT_EQUAL(t[1][1], 11)

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}


//    void Reset(size_t new_row, size_t new_col) {
//
//        matrix.resize(num_rows, vector<int>(num_cols));
//        _table.assign(num_rows, vector<T>(num_cols));
//    }

/*

template <typename T>
class Table {
 private:
  vector<vector<T>> data;

 public:
  Table(size_t rows, size_t columns) {
    Resize(rows, columns);
  }

  const vector<T>& operator [] (size_t idx) const {
    return data[idx];
  }

  vector<T>& operator [] (size_t idx) {
    return data[idx];
  }

  void Resize(size_t rows, size_t columns) {
    data.resize(rows);
    for (auto& item : data) {
      item.resize(columns);
    }
  }

  pair<size_t, size_t> Size() const {
    if (!data.empty() && !data[0].empty()) {
      return {data.size(), data[0].size()};
    }

    return  {0, 0};
  }

};
 */
