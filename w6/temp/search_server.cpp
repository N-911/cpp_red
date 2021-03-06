#include "search_server.h"
#include "iterator_range.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

vector<string> SplitIntoWords_duration(const string& line, TotalDuration& dest) {
    ADD_DURATION(dest);
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }


  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {

//    TotalDuration query_1("Total AddQueriesStream 1");
//    TotalDuration query_2("Total AddQueriesStream 2");
//    TotalDuration query_3("Total AddQueriesStream 3");
//    TotalDuration query_4("Total AddQueriesStream 4");
//    ADD_DURATION(add_query);
  for (string current_query; getline(query_input, current_query); ) {
      // 1
//      const auto words = SplitIntoWords_duration(current_query, query_1);
      const auto words = SplitIntoWords(current_query);
      // 2

      vector<size_t> docid_count(50'000);
      {
//          ADD_DURATION(query_2);
          for (const auto &word : words) {
              for (const size_t docid : index.Lookup(word)) {
                  docid_count[docid]++;
              }
          }
      }


      vector<pair<size_t, size_t>> search_results(50'000);

      for (size_t i = 0; i < 50'000; ++i ) {
          search_results[i] = {i , docid_count[i]};
      }


      //3
      {
//          ADD_DURATION(query_3);

      partial_sort(
              begin(search_results),
              begin(search_results) + 5,
              end(search_results),
              [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                  int64_t lhs_docid = lhs.first;
                  auto lhs_hit_count = lhs.second;
                  int64_t rhs_docid = rhs.first;
                  auto rhs_hit_count = rhs.second;
                  return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
              }
      );

//          partial_sort(docid_count.begin(), docid_count.begin() + 5, docid_count.end());

    }
    //4
      {
//          ADD_DURATION(query_4);
          search_results_output << current_query << ':';

          for (auto[docid, hitcount] : Head(search_results, 5)) {
              if (hitcount != 0) {
                  search_results_output << " {"
                                        << "docid: " << docid << ", "
                                        << "hitcount: " << hitcount << '}';
              }
          }
          search_results_output << endl;
      }

  }
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(document)) {
    index[word].push_back(docid);  // key word = list index of documents where it presents
  }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
