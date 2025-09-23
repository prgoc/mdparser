#include <iostream>
#include <regex>
#include "./models/token.hpp"

using namespace std;

const string TEXT = "text";
const string STRONG = "strong";

const regex STRONG_ELM_REGXP(R"(\*\*(.*?)\*\*)");

Token genTextElement(int id, string text, const Token* parent) {
  return Token {
    id,
    parent,
    TEXT,
    text
  };
}

Token genStrongElement(int id, string text, const Token* parent) {
  return Token {
    id,
    parent,
    STRONG,
    ""
  };
}

auto matchWithStrongRegxp(string text) {
  smatch m;
  regex_search(text, m, STRONG_ELM_REGXP);
  return m;
}