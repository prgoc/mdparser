#include <vector>
#include "merged_token.hpp"

std::string generateHTMLStrimg(std::vector < Token >& tokens);
std::string generate(std::vector < std::vector < Token > > asts);
bool isAllElmParentRoot(std::vector < Token > tokens);