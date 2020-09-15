#pragma once

#include "profile_extendet.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class InvertedIndex {
public:
  void Add(const string& document);
    vector<pair<size_t, size_t>> Lookup(const string& word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }
  const size_t GetDocumentsSize () const {
      return docs.size();
  }

private:
//  unordered_map<string, list<size_t>> index;
  unordered_map<string, vector<pair<size_t, size_t>>> index;
//  vector<list<size_t>> index;
  vector<string> docs;

};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
