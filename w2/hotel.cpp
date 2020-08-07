#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <deque>
#include <queue>

using namespace std;

struct s_hotel {
public :
    s_hotel(int64_t _time, int _client_id, size_t _room_count) : time(_time),
                        client_id(_client_id), room_count(_room_count) {}
    s_hotel() {}

    int64_t time;
    int client_id;
    size_t room_count;
};

class Hotel {
public:
    Hotel() = default;

    void Book(int64_t time, string hotel_name, int client_id, size_t room_count) {
        all_hotels[hotel_name].push({time, client_id, room_count});
        rooms_count[hotel_name] += room_count;
        ++clients_count[hotel_name][client_id];
        current_time = time;
    };

    int Get_current_time() const {
        return current_time;
    }

    int Clients(const string& hotel_name) {
        Update_hotels(hotel_name);
        return clients_count[hotel_name].size();
    }

    int Rooms(const string& hotel_name) {
        Update_hotels(hotel_name);
        return rooms_count[hotel_name];
    }

private:
    int64_t current_time = 0;
    map<string, queue<s_hotel>> all_hotels;
    map<string, int> rooms_count;  // key->hotel_name   value->struct{time, hotel_name, cl_id, room_c}
    map<string, map<int, int>> clients_count;

    void Update_hotels(const string& hotel_name) {
    int cur_t = Get_current_time();

        while (!all_hotels[hotel_name].empty() && all_hotels[hotel_name].front().time <= current_time - 86400) {
            int temp_room = all_hotels[hotel_name].front().room_count;
            int temp_client = all_hotels[hotel_name].front().client_id;

            all_hotels[hotel_name].pop();
            rooms_count[hotel_name] -= temp_room;

            if (clients_count[hotel_name][temp_client] == 1) {
                clients_count[hotel_name].erase(temp_client);
            } else {
                --clients_count[hotel_name][temp_client];
            }
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
            cout << hotels.Rooms(hotel_name) << '\n';
        }
    }

    return 0;
}


/*
 * class HotelManager {
public:
  void Book(int64_t time, const string& hotel_name,
            int client_id, int room_count) {
    current_time_ = time;
    hotels_[hotel_name].Book({time, client_id, room_count});
  }
  int ComputeClientCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  int ComputeRoomCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_);
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) {
      last_bookings_.push(booking);
      room_count_ += booking.room_count;
      ++client_booking_counts_[booking.client_id];
    }
    int ComputeClientCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() {
      const Booking& booking = last_bookings_.front();
      room_count_ -= booking.room_count;
      const auto client_stat_it =
          client_booking_counts_.find(booking.client_id);
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it);
      }
      last_bookings_.pop();
    }
    void RemoveOldBookings(int64_t current_time) {
      while (
          !last_bookings_.empty()
          && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE
      ) {
        PopBooking();
      }
    }
  };

  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};
 */

