#include <vector>
#include <string>
#include <regex>

std::vector < std::string > split(const std::string& str, const std::regex& delim);
void print_token(const Token& token, std::string comment = "");
void show_token(const Token& token);
void show_line(const std::vector < Token >& row);
void show(const std::vector < std::vector < Token > >& asts);