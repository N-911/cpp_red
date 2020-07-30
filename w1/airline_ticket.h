#pragma once

#include <string>
using namespace std;

struct Date {
  int year, month, day;

  /*
public :
    Date(int year_, int month_, int day_) : year(year_), month(month_), day(day_) {}

    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
    */
};

struct Time {
  int hours, minutes;

public:
//    Time(int hours_, int minutes_) : hours(hours_), minutes(minutes_) {}

//    int GetHours() const {
//        return hours;
//    }
//    int GetMinutes() const {
//        return minutes;
//    }

};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};
