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
        Node* node = &lit;
        struct AbstractNode abnode;
        abnode.node.LIT = lit;
        abnode.type = "LITERAL";

        args.push_back(abnode);
        i++;
      }
      FCALL fcall("FCALL", _tokens[i-1][1], args);
      Node* node = &fcall;
      _ast.push_back(node);
      // cout << "Parsed an FCALL Node" << endl;
    }
    // function declaration + definition
    else if(_tokens[i][0] == "WORD" && _tokens[i+1][0] == "WORD" && _tokens[i+2][0] == "O-PAREN" && _tokens[i][1] == "fun") {
      vector<string> name = _tokens[i+1];
      // cout << "Function declaration: " << _tokens[i][1] << "; ";
      vector<Node*> args = {};
      i += 3;
      int parens = 1;
      while(parens > 0) {
        // cout << _tokens[i][0] << endl;
        if(_tokens[i][0] == "O-PAREN") parens++;
        if(_tokens[i][0] == "C-PAREN") {parens--; break;}
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        LITERAL nod("LITERAL", _tokens[i][1], {});
        Node* node = &nod;
        args.push_back(node);
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
      Node* node = &fdecl;
      _ast.push_back(node);
      // par.out("par.ast");

      // cout << "Parsed an FDECL Node" << endl;
    }
    // cout << "Token:" << _tokens[i][0] << " " << _tokens[i][1] << endl;
  }
}

void Parser::printAST() {
  for (int i = 0; i < _ast.size(); i++) {
    Node* sast = _ast[i];
    Node ast = *sast;
    string type = ast._type;
    string value = ast._value;
    vector<Node*> data = ast._data;
    // cout << type << endl;
    cout << type << " " << value << "; data{" << to_string(data.size()) << "}";
    if(type == "FDECL") {
      cout << ((FDECL*)(&ast))->_data2.size() << endl;
      // cout << "; data2{" << to_string((*((FDECL*)(sast)))._data2.size()) << "}";
    }else cout << type;
    cout << endl;
  }
}

void Parser::out(string filename) {
  // write ast into a json-tree like form in output file. (INCLUDING THE AST INSIDE DATA AND DATA2)

  ofstream file;
  file.open(filename);
  file << "{";
  for (int i = 0; i < _ast.size(); i++) {
    Node node = *_ast[i];
    FDECL typedNode = *((FDECL *)(_ast[i]));
    file << "\"" << (*_ast[i])._type << "\": \"" << (*_ast[i])._value << "\"";
    // ast data
    file << ", \"data\": {";
    for (int j = 0; j < node._data.size(); j++) {
      file << "\"" << typedNode._data[j]->_type << "\": \"" << (*_ast[i])._data[j]->_value << "\"";
      if(j != (*_ast[i])._data.size() - 1) {
        file << ",";
      }
    }
    file << "}";
    // ast data2
    if((*_ast[i])._type == "FDECL") {
    file << ", \"data2\": {";
    for (int j = 0; j < (*((FDECL *)(_ast[i])))._data2.size(); j++) {
      file << "\"" << (*((FDECL *)(_ast[i])))._data2[j]->_type << "\": \"" << (*((FDECL *)(_ast[i])))._data2[j]->_value << "\"";
      if(j != (*((FDECL *)(_ast[i])))._data2.size() - 1) {
        file << ",";
      }
    }
    file << "}";
    if(i != _ast.size() - 1) {
      file << ",";
    }
    }
  }
  file << "}";
  file.close();

  /*
  ofstream file;
  file.open(filename);
  file << "{";
  for (int i = 0; i < _ast.size(); i++) {
    file << "\"" << _ast[i]._type << "\": \"" << _ast[i]._value << "\"";
    if(i != _ast.size() - 1) {
      file << ",";
    }
  }
  file << "}";
  file.close();
  */
}