#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {

    int n;
    list <int> sportsmen;
    using Pos = list<int> :: iterator;
//    vector<int> :: iterator> position;

    vector<Pos> position(100'000 + 1 , sportsmen.end());
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int s;
        int next_s;

        cin >> s >> next_s;
        position[s] = sportsmen.insert(position[next_s], s);
    }

    for (auto x: sportsmen) {
        cout << x;
        cout << '\n';
    }
    return 0;
}


/*
 *   const int MAX_ATHLETES = 100'000;
  using Position = list<int>::iterator;
 */