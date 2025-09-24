#include <regex>

/** Generate Text Element */
Token genTextElement(int id, std::string text, const Token* parent);

/** Generate Strong Element */
Token genStrongElement(int id, std::string text, const Token* parent);

/** match with strong regular expression */
std::smatch matchWithStrongRegxp(std::string text);

std::smatch matchWithListRegxp(std::string text) ;