#include "test_runner.h"

#include <vector>
using namespace std;
/*
 * Односвязный список
 */

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList() {
//      while (head)
//          PopFront();

      while(head != nullptr) {
          auto temp = GetHead();
          head = head->next;
          delete temp;
      }
  }

  void PushFront(const T& value) {
      Node* i_node = new Node{value};
//      i_node->value = value;
      i_node->next = head;
      head = i_node;
  }

  void InsertAfter(Node* node, const T& value) {
      if (node == nullptr) {
          PushFront(value);
      } else {
          Node * new_node = new Node;
          new_node->value = value;
          new_node->next = node->next;
          node->next = new_node;
      }
  }

  void RemoveAfter(Node* node) {
      if (node == nullptr) {
          PopFront();
      } else if (node->next != nullptr) {
          auto del_node = node->next;
          node->next = node->next->next;
          delete del_node;
      }

  }

  void PopFront() {
      if (head == nullptr) {
          return;
      }
      auto temp = head;
      if (head->next == nullptr) {
          head = nullptr;
      } else {
          head = head->next;
      }
      delete temp;
  }

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;

};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  const vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // удаляем 3
  list.RemoveAfter(next_to_head); // удаляем 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}


/*
 * template <typename T>
LinkedList<T>::~LinkedList() {
  while (head) {
    PopFront();
  }
}

template <typename T>
void LinkedList<T>::PushFront(const T& value) {
  auto node = new Node{value};
  node->next = head;
  head = node;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value) {
  if (node) {
    auto new_node = new Node{value};
    new_node->next = node->next;
    node->next = new_node;
  } else {
    PushFront(value);
  }
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node* node) {
  if (!node) {
    PopFront();
  } else if (node->next) {
    auto removing_node = node->next;
    node->next = removing_node->next;
    delete removing_node;
  }
}

template <typename T>
void LinkedList<T>::PopFront() {
  if (head) {
    Node* new_head = head->next;
    delete head;
    head = new_head;
  }
}
 */