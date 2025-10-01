#include <map>
#include <regex>

struct Element {
  std::regex regex;
  std::string tag;
};

namespace Leaf {
  const Element THEMATIC_BREAK = {
    std::regex(R"( {0,3}([*_-])[ \t]*(?:\1[ \t]*){2,})"),
    "<hr />"
  };
  namespace Headings {
    const Element ATX_HEADING = {
      std::regex(R"( {0,3}(#{1,6})(?:[ \t]+(.*)(?:[ \t]+#*[ \t]*)?)?)"),
      "h1"
    };
    const Element SETEXT_HEADING = {
      std::regex(""),
      ""
    };
  }
};

namespace Inline {
  const Element STRONG = {
    std::regex(R"(\*\*(.*?)\*\*)"),
    "strong"
  };
};