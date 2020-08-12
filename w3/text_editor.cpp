#include <string>
#include <string_view>
#include <list>

#include "test_runner.h"

using namespace std;

class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() {
//        position_cursor = 0;
//        buffer = "";
//        text_string = "";
    }

    void Left() {  // сдвинуть курсор влево
        if (position_cursor != text_string.begin()) {
            --position_cursor;
        }
    }

    void Right() {  // сдвинуть курсор вправо
        if (position_cursor != text_string.end()) {
            ++position_cursor;
        }
    }

    void Insert(char token) {  // вставить символ token
        text_string.insert(position_cursor, token);
//        ++position_cursor;
    }

    void Cut(size_t tokens = 1) {  // вырезать не более tokens символов, начиная с текущей позиции курсора
        if (tokens) {
            Copy(tokens);
//            text_string.erase(text_string.begin() + position_cursor, text_string.begin() + position_cursor + tokens);
//            text_string.erase (position_cursor, min(position_cursor + tokens, text_string.size()));
            text_string.erase(position_cursor, text_string.end());
        }

    }
    void Copy(size_t tokens = 1) {// cкопироват не более tokens символов начиная с текущей позиции курсора

        auto it = position_cursor + tokens;

        buffer.assign(pos, it);

//        if (tokens) {
//            buffer.clear();
//            buffer = text_string.substr(position_cursor, min (tokens, (text_string.size() - position_cursor)));
//        }
    }
    void Paste() {  // вставить содержимое буфера в текущую позицию курсора
        text_string.insert(position_cursor, buffer);
        position_cursor += buffer.size();
    }
    string GetText() const { // получить текущее содержимое текстового редактора
//        auto res = string_view(text_string);
    return text_string;

    }

private:
    list<char> text_string;
    list<char> buffer;
    list<char> :: iterator position_cursor = text_string.end();
//    size_t position_cursor;
};


void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

void TestCut()
{
    Editor editor;
    //1
    editor.Cut(10);
    editor.Insert('a');
    editor.Left();
    //2
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    //3
    editor.Cut(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    TypeText(editor, "bcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //5
    editor.Cut(5);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    //6
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bcde");
    editor.Right();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bde");
    editor.Cut(1);
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
    Editor editor;
    //1
    editor.Copy(10);
    editor.Insert('a');
    editor.Paste();
    editor.Left();
    ASSERT_EQUAL(editor.GetText(), "a");
    //2
    editor.Copy(1);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");//between a
    //3
    editor.Copy(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");
    TypeText(editor, "bcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcdea");
}

void TestCopyPasteLastChars() {
    Editor editor;
    TypeText(editor, "happy birthday");
    editor.Left();
    editor.Left();
    editor.Copy(5);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "happy birthdayay");
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, TestCut);
  RUN_TEST(tr, TestCopy);
  RUN_TEST(tr, TestCopyPasteLastChars);
  return 0;
}


/*
 *
class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() {
        position_cursor = 0;
        buffer = "";
        text_string = "";
    }

    void Left() {  // сдвинуть курсор влево
        if (position_cursor) {
            --position_cursor;
        }
    }

    void Right() {  // сдвинуть курсор вправо
        if (position_cursor < text_string.size()) {
            ++position_cursor;
        }
    }

    void Insert(char token) {  // вставить символ token
        text_string.insert(position_cursor, {token});
        ++position_cursor;
    }

    void Cut(size_t tokens = 1) {  // вырезать не более tokens символов, начиная с текущей позиции курсора
        if (tokens) {
            Copy(tokens);
//            text_string.erase(text_string.begin() + position_cursor, text_string.begin() + position_cursor + tokens);
//            text_string.erase (position_cursor, min(position_cursor + tokens, text_string.size()));
            text_string.erase (position_cursor, min(tokens, text_string.size() - position_cursor));
        }

    }
    void Copy(size_t tokens = 1) {// cкопироват не более tokens символов начиная с текущей позиции курсора
        if (tokens) {
            buffer.clear();
            buffer = text_string.substr(position_cursor, min (tokens, (text_string.size() - position_cursor)));
        }
    }
    void Paste() {  // вставить содержимое буфера в текущую позицию курсора
        text_string.insert(position_cursor, buffer);
        position_cursor += buffer.size();
    }
    string GetText() const { // получить текущее содержимое текстового редактора
//        auto res = string_view(text_string);
    return text_string;

    }

private:
    string text_string;
    string buffer;
    size_t position_cursor;
};

 */