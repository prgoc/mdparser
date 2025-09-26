#include <iostream>
#include <regex>
#include "token.hpp"
#include "helper.hpp"

using namespace std;

const string TEXT = "text";
const string STRONG = "strong";

const regex STRONG_ELM_REGXP(R"(\*\*(.*?)\*\*)");

Token genTextElement(int id, string text, const Token* parent) {
  const Token tkn {
    id,
    parent,
    TEXT,
    text
  };
  return tkn;
}

Token genStrongElement(int id, string text, const Token* parent) {
  const Token tkn {
    id,
    parent,
    STRONG,
    ""
  };
  return tkn;
}

smatch matchWithStrongRegxp(string text) {
  smatch m;
  regex_search(text, m, STRONG_ELM_REGXP);
  return m;
}

const regex LIST_REGEXP(R"((?:^|\n)( *)([-|\*|\+] (.+))(?:\n|$))");

smatch matchWithListRegxp(string text) {
  smatch m;
  regex_search(text, m, LIST_REGEXP);
  clog << "'" << text << "' is " <<
  (!m.empty()?"a list.": "not a list.")
  << endl;
  return m;
}

vector < string > analyze(string markdown) {
  static const string NEUTRAL_STATE = "neutral_state";
  static const string LIST_STATE = "list_state";
  auto state = NEUTRAL_STATE;

  string lists = "";

  const auto rawMdArray = split(markdown, regex(R"(\r\n|\r|\n)"));
  vector < string > mdArray;

  for(auto index = 0; index < rawMdArray.size(); index++) {
    auto md = rawMdArray[index];
    auto listMatch = regex_search(md, LIST_REGEXP);
    if(state == NEUTRAL_STATE && listMatch) {
      if(index == rawMdArray.size() - 1) {
        lists += md;
        mdArray.push_back(lists);
      }else {
        state = LIST_STATE;
        lists += md + "\n";
      }
    }else if(state == LIST_STATE && listMatch) {
      if(index == rawMdArray.size() - 1) {
        lists += md;
        mdArray.push_back(lists);
      } else {
        lists += md + "\n";
      }
    }else if(state == LIST_STATE && !listMatch) {
      state = NEUTRAL_STATE;
      mdArray.push_back(lists);
      lists = "";
    }

    if(lists.length() == 0) {
      mdArray.push_back(md);
    }
  }

  return mdArray;
}