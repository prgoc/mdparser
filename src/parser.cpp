#include "parser.hpp"
#include "lexer.hpp"
#include <iostream>

using namespace std;

vector < Token > parse(const string& markdownRow) {
  return tokenizeText(markdownRow);
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
        const auto onlyText = genTextElement(id, processingText, parent);
        processingText = "";
        elements.push_back(onlyText);
        continue;
      }

      if(matchArray.position() > 0) {
        id++;
        const auto text = matchArray.prefix();
        const auto textElm = genTextElement(id, text, parent);
        elements.push_back(textElm);
        processingText.erase(0, matchArray.position());
      }

      id++;
      /** newで確保しないとアドレスが無効になる */
      auto elm = new Token;
      *elm = genStrongElement(id, "", parent);

      parent = elm;
      elements.push_back(*elm);

      processingText.erase(0, matchArray.length());
      
      self(self, matchArray[1], parent);
      parent = p;
    }
  };
  tokenize(tokenize, textElement, parent);
  return elements;
}