#include <string>
#include <vector>
using namespace std;

// #define UNIQ_AND_LINE_2(line_number) _a_local_var_##line_number##_uniq
// #define UNIQ_AND_LINE(line_number) UNIQ_AND_LINE_2(line_number)
// #define UNIQ_ID UNIQ_AND_LINE(__LINE__)

#define UNIQ_AND_LINE(line) uniq_id_ + line
#define UNIQ_ID UNIQ_AND_LINE(__LINE__)


int main() {
 int UNIQ_ID = 0;
 string UNIQ_ID = "hello";
 vector<string> UNIQ_ID = {"hello", "world"};
 vector<int> UNIQ_ID = {1, 2, 3, 4};
}

