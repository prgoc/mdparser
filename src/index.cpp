#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include "lexer.hpp"
#include "parser.hpp"
#include "generator.hpp"
#include "helper.hpp"

using namespace std;

auto convertToHTMLString(string markdown) {
  const auto mdArray = analyze(markdown);
  vector < vector < Token > > asts;
  for(const auto& md: mdArray) {
    clog << "------ md ------" << endl
    << md << endl
    << "----------------" << endl;
    asts.push_back(parse(md));
  };
  clog << "parsed:" << endl;
  show(asts);
  const auto htmlString = generate(asts);
  return htmlString;
}

int main(int argc, char* argv[]) {
  ifstream ifs("../test/input.md");
  string input = ""; //"normal text\n \n * **boldlist1**\n * item2";
  stringstream ss;
  ss << ifs.rdbuf();
  input = ss.str();
  cout << "input:" << endl
  << input << endl;
  string output = convertToHTMLString(input);
  cout << "output:" << endl;
  cout << output << endl;
}