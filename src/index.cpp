#include <iostream>
#include <algorithm>
#include <regex>
#include "parser.hpp"
#include "generator.hpp"
#include "helper.hpp"

using namespace std;

auto toAsts(string markdown) {
  const auto mdArray = split(markdown, regex(R"(\r\n|\r|\n)"));
  vector < vector < Token > > asts;
  for(const auto& md: mdArray) {
    asts.push_back(parse(md));
  };
  return asts;
}

auto convertToHTMLString(string markdown) {
  /*
  const auto mdArray = split(markdown, regex(R"(\r\n|\r|\n)"));
  vector < vector < Token > > asts;
  for(const auto& md: mdArray) {
    asts.push_back(parse(md));
  };
  */
  auto asts = toAsts(markdown);
  const auto htmlString = generate(asts);
  return htmlString;
}

int main() {
  string input = "* list1";
  cout << "input: " << input << endl;
  show(toAsts(input));
  cout << convertToHTMLString(input) << endl;
}