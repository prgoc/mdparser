#pragma once

#include <string>

struct Token {
  /** a unique id in a token sequence for the line. to find out where the merged token is located.  */
  int id;
  /** parent token */
  const Token* parent;
  /** element type */
  std::string elmType;
  /** content of token */
  std::string content;
};

struct MergedToken: public Token {
  std::string elmType = "merged";
};