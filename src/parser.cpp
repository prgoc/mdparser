#include "parser.hpp"
#include "lexer.hpp"
#include <iostream>

using namespace std;

vector < Token > parse(const string& markdownRow) {
  return tokenizeText(markdownRow);
}

void _tokenize(string originalText, int id, const Token* p) {
  vector < Token > elements;

}

vector < Token > tokenizeText(string textElement, int initialId, const Token* initialRoot) {
  vector < Token > elements;
  auto parent = initialRoot;
  auto id = initialId;
  const auto tokenize = [&](auto self, string originalText, const Token* p) -> void {
    string processingText = originalText;
    parent = p;
    while(!processingText.empty()) {
      const auto matchArray = matchWithStrongRegxp(processingText);

      if(matchArray.empty()) {
        id++;
        clog << id << " --> " << parent->id << endl;
        const auto onlyText = genTextElement(id, processingText, parent);
        processingText = "";
        elements.push_back(onlyText);
        continue;
      }

      id++;
      clog << id << " --> " << parent->id << endl;
      const auto elm = genStrongElement(id, "", parent);

      parent = &elm;
      elements.push_back(elm);

      processingText.erase(matchArray.position(), matchArray.length());

      self(self, matchArray[1], parent);
      parent = p;
    }
  };
  tokenize(tokenize, textElement, parent);
  return elements;
}