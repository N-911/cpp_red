#include <iostream>
#include <string_view>
#include <sstream>

using namespace std;

string ConcatenateStringViews(
        string_view lhs, string_view rhs) {

    string s;
    s.reserve(lhs.size() + rhs.size());
    return (s += lhs) += rhs;
//    return s += lhs += rhs;
}

int main() {

    string s = "ssmmsmxk m fd oep esd =";

    string l = "left ";
    string r = "right";

    string_view lhs(l);
    string_view rhs(r);

    cout << "function = " << ConcatenateStringViews(lhs, rhs);

    return 0;
}
