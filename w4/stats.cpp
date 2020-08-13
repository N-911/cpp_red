#include "stats.h"
#include <map>

Stats :: Stats() {
    for (int i = 0; i < 5; ++i) {
        methods_status[s_met[i]] = 0;
    }
    for (int i = 0; i < 6; ++i) {
        uri_status[s_uri[i]] = 0;
    }
}

void Stats :: AddMethod(string_view method) {
    size_t i = 0;
    for (; i < 5 && s_met[i] != method; ++i);
    ++methods_status[s_met[i]];
}

void Stats :: AddUri(string_view uri) {
    size_t i = 0;
    for ( ; i < 6 && s_met[i] != uri; ++i);
    ++methods_status[s_uri[i]];
}


const map<string_view, int> & Stats :: GetUriStats() const {
    return uri_status;
}

const map<string_view, int> & Stats :: GetMethodStats() const {
    return methods_status;
}

HttpRequest ParseRequest(string_view line) {
//    string_view str = line;
    vector<string_view> result;

    size_t space2 = line.find_first_not_of(' ');
    line.remove_prefix(space2);

    while(true) {
        size_t space = line.find(' ');
        result.push_back(line.substr(0, space));
        if (space == line.npos) {
            break;
        } else {
            line.remove_prefix(space + 1); }
    }
    return HttpRequest{result[0], result[1], result[2]};


}
