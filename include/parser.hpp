#include <vector>
#include "token.hpp"

const auto rootToken = Token {
  0,
  nullptr,
  "root",
  ""
};

std::vector < Token > parse(const std::string& markdownRow);
std::vector < Token > tokenizeText(std::string textElement, int initialId = 0, const Token* initialRoot = &rootToken);