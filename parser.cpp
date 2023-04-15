#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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
      vector<AbstractNode> args = {};
      i += 2;
      while(_tokens[i][0] != "C-PAREN") {
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        // args.push_back(Node("LITERAL", _tokens[i][1], {}));
        LITERAL lit("LITERAL", _tokens[i][1], {});
        struct AbstractNode abnode;
        abnode._type = "LITERAL";
        abnode._LIT = lit;

        args.push_back(abnode);
        i++;
      }
      FCALL fcall("FCALL", _tokens[i-1][1], args);
      AbstractNode node;
      node._type = "FCALL";
      node._FC = fcall;
      _ast.push_back(node);
      // cout << "Parsed an FCALL Node" << endl;
    }
    // function declaration + definition
    else if(_tokens[i][0] == "WORD" && _tokens[i+1][0] == "WORD" && _tokens[i+2][0] == "O-PAREN" && _tokens[i][1] == "fun") {
      vector<string> name = _tokens[i+1];
      // cout << "Function declaration: " << _tokens[i][1] << "; ";
      vector<AbstractNode> args = {};
      i += 3;
      int parens = 1;
      while(parens > 0) {
        // cout << _tokens[i][0] << endl;
        if(_tokens[i][0] == "O-PAREN") parens++;
        if(_tokens[i][0] == "C-PAREN") {parens--; break;}
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        LITERAL nod("LITERAL", _tokens[i][1], {});
        AbstractNode abnode;
        abnode._type = "LITERAL";
        abnode._LIT = nod;
        args.push_back(abnode);
        i++;
      }
      i += 2;
      vector<vector<string>> body = {};
      while(_tokens[i][0] != "C-BRACE") {
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        body.push_back(_tokens[i]);
        i++;
      }
      // parse body
      Parser par(body);
      par.parse();
      FDECL fdecl("FDECL", name[1], args, par._ast);
      AbstractNode abnode;
      abnode._type = "FDECL";
      abnode._FD = fdecl;
      _ast.push_back(abnode);
      // par.out("par.ast");

      // cout << "Parsed an FDECL Node" << endl;
    }
    // cout << "Token:" << _tokens[i][0] << " " << _tokens[i][1] << endl;
  }
}

