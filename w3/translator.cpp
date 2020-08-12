#include "test_runner.h"
#include <string>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
    string_view copy_source;
    string_view copy_target;

    if (const auto it = m_source.find(source); it != m_source.end()) {
        copy_source = it->first;
    } else {
        copy_source = strings_storage.emplace(source);
    }
      if (const auto it = m_target.find(target); it != m_target.end()) {
          copy_target = it->first;
      } else {
          copy_target = strings_storage.emplace(target);
      }

      m_source[copy_source] = copy_target;
      m_target[copy_target] = copy_source;

  }

  string_view TranslateForward(string_view source) const {
      auto res = m_source.find(source);

      if (res == m_source.end()) {
          return string{};
      } else {
          return res->second;
      }
  }

  string_view TranslateBackward(string_view target) const {
      auto res = m_target.find(target);

      if (res == m_target.end()) {
          return string{};
      } else {
          return res->second;
      }
  }

private:
    map<string_view, string_view> m_source;
    map<string_view, string_view> m_target;
    queue<string> strings_storage;


};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}
void TestFunctional() {
    Translator translator;
    string l("stol");
    translator.Add(string("okno"), string("window"));
    translator.Add(l, string("table"));
    translator.Add(l, string("truba"));
    translator.Add(l, string("knopka"));
    l.clear();
    translator.Add(string("kopa"), string("opa"));
    translator.Add(string("lopa"), string("opa"));
    translator.Add(string("jola"), string("opa"));
    string t("kakashka");
    translator.Add(string_view(t), string_view("iop"));
    translator.Add(string_view(t), string_view("yota"));
    translator.Add(string_view(t), string_view("rota"));
    translator.Add(string_view("trully"), string_view("gonep"));
    translator.Add(string_view("kaka"), string_view("gonep"));
    translator.Add(string_view("lui"), string_view("gonep"));
    t.clear();

    ASSERT_EQUAL(translator.TranslateForward("stol"), "knopka");
    ASSERT_EQUAL(translator.TranslateBackward("knopka"), "stol");
    ASSERT_EQUAL(translator.TranslateForward("lopa"), "opa");
    ASSERT_EQUAL(translator.TranslateBackward("opa"), "jola");
    ASSERT_EQUAL(translator.TranslateForward("kakashka"), "rota");
    ASSERT_EQUAL(translator.TranslateBackward("gonep"), "lui");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  RUN_TEST(tr, TestFunctional);
  return 0;

}


/*
 * private:
  string_view GetClonedView(string_view s) {
    for (const auto* map_ptr : {&forward_dict, &backward_dict}) {
      const auto it = map_ptr->find(s);
      if (it != map_ptr->end()) {
        return it->first;
      }
    }
    return data.emplace_back(s);
  }

  static string_view Translate(const map<string_view, string_view>& dict, string_view s) {
    if (const auto it = dict.find(s); it != dict.end()) {
      return it->second;
    } else {
      return {};
    }
  }


 */