#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"

using namespace std;

// why is regex is c++ such a pain? :sob:
// in*
// its not that bad*

int main() {

  Lexer lexer("test.lang");
  regex regexp(lexer.tokenRegex[3][1]);

  cout << "In: " << lexer._string << endl;
  cout << "Lexer: " << endl << endl;

  // lol 1/8th of the way there.. :gun: :me:
  lexer.tokenize();
  cout << lexer._tokens.size() << endl;
  lexer.printTokens();

  cout << "Parser: " << endl << endl;

  Parser parser(lexer._tokens);
  parser.parse();
  parser.printAST();

  cout << "Out: " << endl << endl;

  return 0;
}