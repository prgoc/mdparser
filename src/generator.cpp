#include <vector>
#include <algorithm>
#include <sstream>
#include "merged_token.hpp"

using namespace std;

string generateHTMLString(vector < Token >& tokens) {
  string htmlString;
  for(const auto token: tokens) {
    htmlString = token.content + htmlString;
  }
  return htmlString;
}

bool isAllElmParentRoot(vector < Token > tokens) {
  return all_of(tokens.begin(), tokens.end(), [](Token t) {
    return t.parent != nullptr && t.parent->elmType == "root";
  });
}

struct Parentheses {
  char open;
  char close;
};

auto getInsertPosition(string content) {
  const auto tag = Parentheses {
    '<',
    '>'
  };
  auto pos_open = content.find_first_of(tag.open);
  auto position = content.find_first_of(tag.close, pos_open);
  return position + 1;
}

string createMergedContent(Token currentToken, Token parentToken) {
  string content;
  if(parentToken.elmType == "strong") {
    content = "<strong>" + currentToken.content + "</strong>";
  }else if(parentToken.elmType == "merged") {
    const auto position = getInsertPosition(parentToken.content);
    content = parentToken.content.substr(0, position) + currentToken.content + parentToken.content.substr(position);
  }
  return content;
}

string generate(vector < vector < Token > > asts) {
  string htmlStrings;
  for(auto& lineTokens: asts) {
    reverse(lineTokens.begin(), lineTokens.end());
    auto rearrangedAst = lineTokens;
    while(!isAllElmParentRoot(rearrangedAst)) {
      auto iterator = rearrangedAst.begin();
      while(iterator != rearrangedAst.end()) {
        if(iterator->parent && iterator->parent->elmType == "root") {
          iterator++;
          continue;
        }
        const auto currentToken = iterator;
        iterator = rearrangedAst.erase(iterator);
        const auto parentToken = find_if(
          rearrangedAst.begin(),
          rearrangedAst.end(),
          [&](Token t) {
            return t.id == currentToken->parent->id;
          });
        const MergedToken mergedToken {
          parentToken->id,
          parentToken->parent,
          "merged",
          createMergedContent(*currentToken, *parentToken)
        };
        *parentToken = mergedToken;
      }
    }
    htmlStrings += generateHTMLString(rearrangedAst);
  }
  return htmlStrings;
}