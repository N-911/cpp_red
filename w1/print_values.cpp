#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl



int main() {
  TestRunner tr;
  int x = 5;
  int y = 6;

    {
//        ostringstream output;
        for (auto i = 0; i < 5; ++i)
            PRINT_VALUES(cout, x, y);
//        PRINT_VALUES(cout, x, "red belt");
    }

    {
        tr.RunTest([] {
            ostringstream output;
            PRINT_VALUES(output, 5, "red belt");
            ASSERT_EQUAL(output.str(), "5\nred belt\n");
        }, "PRINT_VALUES usage example");
    }
    {
        int x = 2;
        int y = 4;
        tr.RunTest([x, y] {
            ostringstream output;
            if (x ==  y) {
                PRINT_VALUES(output, x + y, "red belt");
                PRINT_VALUES(output, x - y, "red belt");
            }
            else {
                PRINT_VALUES(output, y, "red belt");
            }
            ASSERT_EQUAL(output.str(), "4\nred belt\n");
        }, "PRINT_VALUES usage example  if ");
    }
    {
        string a = ";";
        string b = "{ ; }";

        int x = 2;
        int y = 2;
        tr.RunTest([x, y, a,b] {
            ostringstream output;
            if (x ==  y) {
                PRINT_VALUES(output, a, "red belt");
//                PRINT_VALUES(output, b, "red belt");
            }
            else {
                PRINT_VALUES(output, y, "red belt");
            }
            ASSERT_EQUAL(output.str(), ";\nred belt\n");
        }, "PRINT_VALUES usage example  if 2");
    }

}


