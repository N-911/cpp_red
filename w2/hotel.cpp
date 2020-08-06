#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <deque>


using namespace std;

bool Cmp_time(const int& time_1, const int& time_2) {
    return time_1 < time_2;

}
struct s_hotel {

public :

    s_hotel(int _time, string _hotel_name, int _client_id, size_t _room_count) : time(_time),
                   hotel_name(_hotel_name), client_id(_client_id), room_count(_room_count) {}
    s_hotel() {}
    int time;
    string hotel_name;
    int client_id;
    size_t room_count;
};




class Hotel {
public:

    Hotel() = default;

    void Book(int time, string hotel_name, int client_id, size_t room_count) {
        all_hotels[hotel_name].push_back(s_hotel({time, hotel_name, client_id, room_count}));
        hotel_rooms[hotel_name] += room_count;
        current_time = time;
        Update_hotels(hotel_name);
    };

    int Get_current_time() const {
        return current_time;
    }

    int Clients(string hotel_name) {

        Update_hotels(hotel_name);


//        auto it_clients =
//        auto res = *it;
//        cout << res.time << ' ' << res.hotel_name << endl;
//        return all_hotels[hotel_name].end() - it;
    return 0;

    }

    int Rooms(string hotel_name) {

        return hotel_rooms[hotel_name];
    }
private:
//    vector<s_hotel> hotels;
    int current_time;
    map<string, vector<s_hotel>> all_hotels;
    map<string, int> hotel_rooms;

//    map<string, int> all_room;

    void Update_hotels(string hotel_name) {
    int cur_t = Get_current_time();
    auto it = lower_bound(all_hotels[hotel_name].begin(), all_hotels[hotel_name].end(), s_hotel(),
                          [cur_t](const s_hotel& lhs, const s_hotel& rhs){
                              return lhs.time < (cur_t - 86400); } );
    vector<s_hotel> temp = {it, all_hotels[hotel_name].end()};
    all_hotels[hotel_name] = temp;
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
            int time;
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
