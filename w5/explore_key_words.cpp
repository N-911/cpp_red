#include "test_runner.h"
#include "profile.h"

#include <functional>
#include <map>
#include <string>
#include <future>
#include <sstream>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
      for (const auto& [key, value] : other.word_frequences) {
          word_frequences[key] += value;
      }
  }
};


Stats ExploreLine(const set<string>& key_words, const string& line) {
    istringstream s_line(line);
    string temp;
    Stats result;

    for ( ; !s_line.eof(); ) {
        s_line >> temp;
        if (auto count = key_words.count(temp); count != 0) {
            result.word_frequences[temp] += count;
        }
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
  Stats result;

  for (string line; getline(input, line); ) {
      result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreLines(const set<string>& key_words, const vector<string>& part_lines) {
    Stats result;

    for (const auto& line : part_lines) {
        result += ExploreLine(key_words, line);
    }
    return result;
}





Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;

    vector<future<Stats>> f_vector;
    vector<string> part_lines;
    int count_line = 0;

    for (string line; getline(input, line); ) {
        if (count_line == 5000 ) {
            f_vector.push_back(async(ExploreLines, ref(key_words), part_lines));
            count_line = 0;
            part_lines.clear();
        }
        part_lines.push_back(move(line));
        count_line++;
    }
    if (count_line) {
        f_vector.push_back(async(ExploreLines, ref(key_words), part_lines));
    }

    for (auto& elem : f_vector) {
        result += elem.get();
    }
    return result;
}


 /*
Stats ExploreLines(const vector<string>& lines, const set<string>& key_words) {
    Stats stats;
    for (const auto& line : lines) {
        stats += ExploreLine(key_words, line);
    }
    return stats;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<vector<string>> lines(4);

    int count = 0;
    for (string line; getline(input, line); ) {
        lines[count / 5000].push_back(line);
        count++;
    }

    vector<future<Stats>> futures;
    for (auto thread : lines) {
        futures.push_back(async([=] { return ExploreLines(thread, key_words); }));
    }
    Stats word_frequences;
    for (auto& future : futures) {
        word_frequences += future.get();
    }
    return word_frequences;

}

 */
void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
