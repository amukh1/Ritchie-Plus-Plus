#include <string>
#include <vector>
#include <iostream>

#include "parser.h"

using namespace std;

Parser::Parser(vector<vector<string>> tokens) {
  _tokens = tokens;
}

void Parser::printTokens() {
  for (int i = 0; i < _tokens.size(); i++) {
    cout << _tokens[i][0] << " " << _tokens[i][1] << endl;
  }
}

void Parser::parse() {
  for (int i = 0; i < _tokens.size(); i++) {
    // just for testing, kicks n giggles
    // function call
    if(_tokens[i][0] == "WORD" && _tokens[i+1][0] == "O-PAREN") {
      // cout << "Function call: " << _tokens[i][1] << "; ";
      vector<Node> args = {};
      i += 2;
      while(_tokens[i][0] != "C-PAREN") {
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        args.push_back(Node("LITERAL", _tokens[i][1], {}));
        i++;
      }

      _ast.push_back(Node("FCALL", _tokens[i-1][1], args));

      cout << endl;
    }
    // cout << "Token:" << _tokens[i][0] << " " << _tokens[i][1] << endl;
  }
}

void Parser::printAST() {
  for (int i = 0; i < _ast.size(); i++) {
    cout << _ast[i]._type << " " << _ast[i]._value << "; data{" << to_string(_ast[i]._data.size()) << "}" << endl;
  }
}