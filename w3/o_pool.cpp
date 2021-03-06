#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
      T* new_ob;

      if (!freed_object.empty()) {
          new_ob = freed_object.front();
          freed_object.pop();
          active_object.insert(new_ob);
      } else {
          new_ob = new T;
          active_object.insert(new_ob);
      }
      return new_ob;
  }

  T* TryAllocate() {
      T* new_ob;

      if (!freed_object.empty()) {
          new_ob = freed_object.front();
          freed_object.pop();
          active_object.insert(new_ob);
      } else {
          new_ob = nullptr;
      }
      return new_ob;

  }

  void Deallocate(T* object) {
      if (active_object.count(object) == 0) {
          throw invalid_argument ("invalid_argument");
      }
      auto it = active_object.find(object);
      freed_object.push(*it);
      active_object.erase(object);
  }

  ~ObjectPool() {
      for (auto x : active_object) {
          delete x;
      }
      while (!freed_object.empty()) {
          delete freed_object.front();
          freed_object.pop();
      }
  }

private:
    set<T*> active_object;
    queue<T*> freed_object;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}


/*
 * private:
  queue<T*> free;
  set<T*> allocated;
};

template <typename T>
T* ObjectPool<T>::Allocate() {
  if (free.empty()) {
    free.push(new T);
  }
  auto ret = free.front();
  free.pop();
  allocated.insert(ret);
  return ret;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
  if (free.empty()) {
    return nullptr;
  }
  return Allocate();
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
  if (allocated.find(object) == allocated.end()) {
    throw invalid_argument("");
  }
  allocated.erase(object);
  free.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
  for (auto x : allocated) {
    delete x;
  }
  while (!free.empty()) {
    auto x = free.front();
    free.pop();
    delete x;
  }
}

 */