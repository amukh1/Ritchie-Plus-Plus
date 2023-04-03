#include <iostream>
#include "lexer.h"

using namespace std;

int main()
{
    Lexer lexer("test.lang");
    lexer.tokenize(lexer._string);
    lexer.printTokens();
    return 0;
}