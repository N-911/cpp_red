
template <typename T>
struct ReadOnlyValue {
    const T value;
};

template <typename T>
ReadOnlyValue<T> MakeReadOnly(T x) {
    return {x};
}


//*********************************************
template <typename It>
struct IteratorRange {
    It first, last;

    IteratorRange(It begin, It end)
            : first(begin)
            , last(end)
    {
    }
};

vector<int> v;
IteratorRange<vector<int>::iterator> vi_rng{begin(v), end(v)};


vector<string> vs;
IteratorRange vs_rng(vs.begin(), vs.end());

//**********************************

template <typename T>
auto Middle(T& container) {
    return container.begin() + container.size() / 2;
}

int main() {
    vector<string> words = {"C++", "Red", "Belt", "Templates"};
    auto mid = Middle(words);
}

//**********************************

template <typename T>
auto Middle(T& container) {
    return container.begin() + container.size() / 2;
}

int main() {
    const deque<int> numbers = {10, 20, 30, 45, 50};
    auto mid = Middle(numbers);
}

//****************************************

template <typename It>
struct IteratorRange {
    It first, last;

    IteratorRange(It begin, It end)
            : first(begin)
            , last(end)
    {
    }
};

template<typename T>
auto MakeRange(T& container) {
    return IteratorRange(container.begin(), container.end());
}


string s = "Hello, world!";
auto rng = MakeRange(s);

const string s = "Hello, world!";
IteratorRange<string::const_iterator> rng = MakeRange(s);

IteratorRange vs_d(10, 23);




//  deque

template <typename T>
class Deque {
private:
    vector<T> head, tail;

    T& AtImpl(size_t i) {
        return i < head.size() ? head[head.size() - i - 1] : tail[i - head.size()];
    }

    void CheckIndex(size_t i) const {
        if (i >= Size())
            throw out_of_range("Index is out of range");
    }

public:
    Deque() = default;

    bool Empty() const {
        return head.empty() && tail.empty();
    }

    size_t Size() const {
        return head.size() + tail.size();
    }

    void Clear() {
        head.clear();
        tail.clear();
    }

    const T& operator [] (size_t i) const {
        return AtImpl(i);
    }

    T& operator [] (size_t i) {
        return AtImpl(i);
    }

    const T& At(size_t i) const {
        CheckIndex(i);
        return AtImpl(i);
    }

    T& At(size_t i) {
        CheckIndex(i);
        return AtImpl(i);
    }

    const T& Front() const {
        return head.empty() ? tail.front() : head.back();
    }

    T& Front() {
        return head.empty() ? tail.front() : head.back();
    }

    const T& Back() const {
        return tail.empty() ? head.front() : tail.back();
    }

    T& Back() {
        return tail.empty() ? head.front() : tail.back();
    }

    void PushFront(const T& elem) {
        head.push_back(elem);
    }

    void PushBack(const T& elem) {
        tail.push_back(elem);
    }
};

#include <vector>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin)
            , last(end)
            , size_(distance(first, last))
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator {
private:
    vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (size_t left = distance(begin, end); left > 0; ) {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

