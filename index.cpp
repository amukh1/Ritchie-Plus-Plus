#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"
#include "AST.h"

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
  // lexer.printTokens();

  cout << "Parser: " << endl << endl;

  Parser parser(lexer._tokens);
  // cout << "parse started" << endl;
  parser.parse();
  // cout << "parsing done" << endl;
  // cout << (*(FDECL*)(parser._ast[0]))._data2[0]->_type << endl;
  // parser.printAST();
  // parser.out("out.ast");
  // cout << ((FDECL*)(parser._ast[0]))->_data2.size() << endl;

  cout << "Out: " << endl << endl;

  return 0;
}