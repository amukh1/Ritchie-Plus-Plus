#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "AST.h"

using namespace std;

class Parser {
public:
  vector<vector<string>> _tokens;
  int _cursor = 0;
  vector<AbstractNode> _ast;


  Parser(vector<vector<string>> tokens);
  // ~parser();

  void printTokens();

  void parse();

  void printAST();

  void out(string filename);
};