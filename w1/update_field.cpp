#include "airline_ticket.h"
#include "test_runner.h"


#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;


#define UPDATE_FIELD(ticket, field, values) \
  {                                         \
    auto it = values.find(#field);          \
    if (it != values.end()) {               \
      istringstream is(it->second);         \
      is >> ticket.field;                   \
    }                                       \
  }



istream& operator >> (istream& stream, Date& date) {
    int year, month, day;
    stream >> year;
    stream.ignore(1);
    stream >> month;
    stream.ignore(1);
    stream >> day;
    date.month = month;
    date.year = year;
    date.day = day;
    return stream;
}

istream& operator >> (istream& is, Time& time) {
    int hour, min;
    is >> hour;
    is.ignore(1);
    is >> min;
    time.hours = hour;
    time.minutes = min;
    return is;
}

bool operator < (const Date& lhs, const Date& rhs) {
    return vector<int>{lhs.year, lhs.month, lhs.day} < vector<int>{rhs.year, rhs.month, rhs.day};
}

bool operator == (const Date& lhs, const Date& rhs) {
    return vector<int>{lhs.year, lhs.month, lhs.day} ==
           vector<int>{rhs.year, rhs.month, rhs.day};
}

bool operator < (const Time& lhs, const Time& rhs) {
    return vector<int>{lhs.hours, lhs.minutes} < vector<int> {rhs.hours, rhs.minutes};
}

bool operator == (const Time& lhs, const Time& rhs) {
    return vector<int>{lhs.hours, lhs.minutes} == vector<int> {rhs.hours, rhs.minutes};
}

ostream& operator <<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.year <<
           "-" << setw(2) << setfill('0') << date.month <<
           "-" << setw(2) << setfill('0') << date.day;
    return stream;
}


ostream& operator << (ostream& stream, const Time& time) {
    return stream << time.hours << ":" << time.minutes << endl;
}

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time


void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
UPDATE_FIELD(t, departure_date, updates1);
UPDATE_FIELD(t, departure_time, updates1);
UPDATE_FIELD(t, price, updates1);

ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
ASSERT_EQUAL(t.price, 0);

const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
};
UPDATE_FIELD(t, departure_date, updates2);
UPDATE_FIELD(t, departure_time, updates2);
UPDATE_FIELD(t, arrival_time, updates2);
UPDATE_FIELD(t, price, updates2);


  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}

