#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;


class ReadingManager {
public:
    ReadingManager()
            : user_pages_read(MAX_USER_COUNT_ + 1, 0),    //    user[count read pages]
              pages_stat(1001, 0),                        //    pages_stat[count user who read ]
              count_users(0) {}                                 //      init how many user read specific page

    void Read(int user_id, int page_count) {
        int current_page = user_pages_read[user_id];

        user_pages_read[user_id] = page_count;
        if (current_page == 0) {
            ++count_users;
        } else {
            --pages_stat[current_page];
        }
        ++pages_stat[page_count];
    }

    double Cheer(int user_id) const {
        if (user_pages_read[user_id] == 0) {
            return 0;                 // Если для данного пользователя пока не было ни одного события READ, доля считается равной 0,
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        const int page_count = user_pages_read[user_id];  // количество прочитаних страниц current user

        int rs = 0;

        for (int a = 0; a < page_count; ++a) {
            if (pages_stat[a] != 0)
                rs += pages_stat[a];
        }
        if (rs == 0) {
            return 0;
        }
        return (rs) * 1.0 / (count_users - 1);
    }

private:
    vector<int> pages_stat;
    int count_users;
    vector<int> user_pages_read;  // вектор [user_id] = page_counts

    static const int MAX_USER_COUNT_ = 100'000;

    int GetUserCount() const {
        return count_users;
    }
};



int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
