#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include "token.hpp"

using namespace std;

vector < string > split(const string& str, const regex& delim) {
  vector < string > v = {
    str
  };
  smatch m;
  while(regex_search(v.back(), m, delim)) {
    v.pop_back();
    if(m.prefix() != "") {
      v.push_back(m.prefix());
    }
    if(m.suffix() != "") {
      v.push_back(m.suffix());
    }
  }
  return v;
}

void print_token(const Token& t, string comment) {
  clog << comment
  << "(" << t.id << ") "
  << "[" << t.elmType << "] "
  << "'" << t.content << "'"
  << " --> " << t.parent->id << endl;
}

void show_token(const Token& t) {
  clog << "    { "
  << "id: " << t.id << ", "
  << "elmType: '" << t.elmType << "', "
  << "content: '" << t.content << "', "
  << "parent: " << (t.parent)->id << " }" << endl;
}

void show_line(const vector < Token >& row) {
  clog << "  [ " << endl;
  for(const auto& t: row) {
    show_token(t);
  }
  clog << "  ]" << endl;
}

void show(const vector < vector < Token > >& asts) {
  clog << "[ " << endl;
  for(const auto& row: asts) {
    show_line(row);
  }
  clog << "]" << endl;
}