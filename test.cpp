#include <iostream>
#include <regex>
#include <vector>

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

int main() {
  string name = "john";
  smatch m;
  const string str = "str45jazz67bar";
  vector < string > v = split(str, regex(R"(\d+)"));
  regex_search(str, m, regex(R"((\D+\d+))"));
  cout << "prefix: " << m.prefix() << endl;
  for(const auto& e: v) {
    cout << "match: " << e << endl;
  }
  cout << "suffix: " << m.suffix() << endl;

  cout << "hello, " << name << "!" << endl;
  return 0;
}