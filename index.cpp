#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

#include "lexer.h"
#include "parser.h"
#include "AST.h"
#include "jsonify.h"

using namespace std;

// why is regex is c++ such a pain? :sob:
// in*
// its not that bad*

int main() {
  string filename = "out2.json";
  ofstream file;
  file.open(filename);

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
  cout << parser._ast[0]._FD.body.size() << endl;
  string json = stringify(parser._ast[0]);
  // cout << "parsing done" << endl;
  // cout << (*(FDECL*)(parser._ast[0])).body[0]->_type << endl;
  // parser.printAST();
  // parser.out("out.ast");
  // cout << ((FDECL*)(parser._ast[0]))->body.size() << endl;

  cout << "Out: " << endl << endl;
  cout << parser._ast[0]._FD.codegen() << endl;

  file << json;

  return 0;
}