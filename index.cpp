#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "lexer.h"

using namespace std;

int main()
{
    Lexer lexer("test.lang");
    lexer.tokenize(lexer._string);
    lexer.printTokens();

    // why is regex is c++ such a pain? :sob:
    bool const reg = regex_search(" hello e", regex("/^\\s+/"));
    cout << reg << endl;

    return 0;
}