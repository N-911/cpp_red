#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <deque>

using namespace std;


struct s_hotel {
public :
    s_hotel(int _time, int _client_id, size_t _room_count) : time(_time),
                        client_id(_client_id), room_count(_room_count) {}
    s_hotel() {}
    int time;
//    string hotel_name;
    int client_id;
    size_t room_count;
};

class Hotel {
public:
    Hotel() = default;

    void Book(int time, string hotel_name, int client_id, size_t room_count) {
        all_hotels[hotel_name].push_back(s_hotel({time, client_id, room_count}));
        rooms_count[hotel_name] += room_count;
        current_time = time;
    };

    int Get_current_time() const {
        return current_time;
    }

    int Clients(const string& hotel_name) {
        Update_hotels(hotel_name);

    return 0;
    }
    int Rooms(const string& hotel_name) {
        Update_hotels(hotel_name);
        return rooms_count[hotel_name];
    }

private:
    int64_t current_time = 0;
    map<string, deque<s_hotel>> all_hotels;
    map<string, int> rooms_count;  // key->hotel_name   value->struct{time, hotel_name, cl_id, room_c}

    void Update_hotels(string hotel_name) {
    int cur_t = Get_current_time();

    while (!all_hotels[hotel_name].empty() && all_hotels[hotel_name].front().time <= current_time - 86400) {
        int temp = all_hotels[hotel_name].front().room_count;
        all_hotels[hotel_name].pop_front();
        rooms_count[hotel_name] -=temp;

        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Hotel hotels;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            int user_id;
            int room_count;

            cin >> time >> hotel_name >> user_id >> room_count;
            hotels.Book(time, hotel_name, user_id, room_count);

        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.Clients(hotel_name) << "\n";

        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.Rooms(hotel_name);
        }
    }

    return 0;
}


//        auto it_clients =
//        auto res = *it;
//        cout << res.time << ' ' << res.hotel_name << endl;
//        return all_hotels[hotel_name].end() - it;

//    auto it = lower_bound(all_hotels[hotel_name].begin(), all_hotels[hotel_name].end(), s_hotel(),
//                          [cur_t](const s_hotel& lhs, const s_hotel& rhs){
//                              return lhs.time < (cur_t - 86400); } );
//    vector<s_hotel> temp = {it, all_hotels[hotel_name].end()};

/*
 * bool Cmp_time(const int& time_1, const int& time_2) {
    return time_1 < time_2;

}
 */