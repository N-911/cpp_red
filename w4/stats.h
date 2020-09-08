#pragma once

#include "http_request.h"
#include <string>
#include <vector>
#include <array>
#include <string_view>
#include <map>

using namespace std;

class Stats {

public:
  Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;

private:
    map<string_view, int> methods_status;
    map<string_view, int> uri_status;
    inline static const array<string, 5> s_met {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
    inline static const array<string, 6> s_uri {"/", "/order", "/product", "/basket", "/help", "unknown"};
};

HttpRequest ParseRequest(string_view line);
