#include <iostream>
#include <algorithm>
#include <regex>
#include "parser.hpp"

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

auto convertToHTMLString(string markdown) {
  const auto mdArray = split(markdown, regex(R"(\r\n|\r|\n)"));
  vector < vector < Token > > asts;
  for(const auto& md: mdArray) {
    asts.push_back(parse(md));
  };
  return asts;
}

int main() {
  cout << "[ " << endl;
  for(auto row: convertToHTMLString("**bold**")) {
    cout << "  [ " << endl;
    for(auto t: row) {
      cout << "    { "
      << "id: " << t.id << ", "
      << "elmType: '" << t.elmType << "', "
      << "content: '" << t.content << "', "
      << "parent: " << (t.parent)->id << " }" << endl;
    }
    cout << "  ]" << endl;
  }
  cout << "]" << endl;
}