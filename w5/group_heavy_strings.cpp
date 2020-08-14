#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

/*
 * Дан набор строк. Необходимо разбить их на группы, в каждой из которых все строки имеют одинаковый набор символов.

    Например, если даны строки law, port, top, laptop, pot, paloalto, wall, awl, нужно разбить их на 4 группы:

    строки, состоящие только из букв a, l и w: law, wall, awl;
    строки, состоящие только из букв o, p, r и t: port;
    строки, состоящие только из букв o, p и t: top, pot;
    строки, состоящие только из букв a, l, o, p, t: laptop, paloalto.

 */
using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;


template <typename String>
set<Char<String>> get_sorted_and_uniq(const String& st) {
//    set<Char<String>> res (st.begin(), st.end());
    return {st.begin(), st.end()};
    }

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {

    map <set<Char<String>>,  Group<String>> data;
    for (auto& s : strings) {
        data[get_sorted_and_uniq(s)].push_back(move(s));
    }
    vector<Group<String>> res;
    for (auto& [key, group] : data) {
        res.push_back(move(group));
    }
    return res;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}

/*
 * template <typename String>
using Key = String;


template <typename String>
Key<String> ComputeStringKey(const String& string) {
  String chars = string;
  sort(begin(chars), end(chars));
  chars.erase(unique(begin(chars), end(chars)), end(chars));
  return chars;
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  map<Key<String>, Group<String>> groups_map;
  for (String& string : strings) {
    groups_map[ComputeStringKey(string)].push_back(move(string));
  }
  vector<Group<String>> groups;
  for (auto& [key, group] : groups_map) {
    groups.push_back(move(group));
  }
  return groups;
}

 */