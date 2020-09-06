#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;
/*
 * шаблонный контейнер PriorityCollection, позволяющий хранить объекты некопируемого типа,
 * а также совершать с ними следующие операции:
 *
 * - добавить элемент с нулевым приоритетом;
 * - добавить набор элементов с нулевыми приоритетами;
 * - увеличить на 1 приоритет заданного элемента;
 * - извлечь из контейнера элемент с максимальным приоритетом.
 *
 * Поскольку добавление элемента заключается в его перемещении в контейнер, метод увеличения
 * приоритета не может принимать сам элемент. Поэтому метод, добавляющий элементы,
 * для каждого из них должен вернуть некий идентификатор,
 * который затем можно использовать для вызова других методов.
 */

template <typename T>
class PriorityCollection {
public:
  using Id = int;
  using Priority = int;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
      Id id_object = object_added.size();
      object_added.push_back({move(object)});
      sorted_object.insert({0, id_object});
      return id_object;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {

      for (; range_begin != range_end; ++range_begin ) {
          *ids_begin++ = Add(move(*range_begin));
      }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
        if (id >= 0 && id < object_added.size() && object_added[id].priority != -1) {
            return true;
        }
      return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
      return object_added[id].object;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
      auto& item = object_added[id];
      const int old_priority = item.priority;
      const int new_priority = ++item.priority;
      sorted_object.erase({old_priority, id});
      sorted_object.insert({new_priority, id});
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, Priority> GetMax() const {
      const auto& item = object_added[prev(sorted_object.end())->second];
      return {item.object, item.priority};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, Priority> PopMax() {
      const auto it = prev(sorted_object.end());
      auto& temp = object_added[it->second];
      sorted_object.erase(it);
      const int priority = temp.priority;
      temp.priority = -1;
      return {move(temp.object), priority};
  }

private:
    struct p_container {
        T object;
        int priority = 0;
    };
    vector<p_container> object_added;
    set<pair<Priority, Id>> sorted_object;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
