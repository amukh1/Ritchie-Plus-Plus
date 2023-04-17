#include <string>
#include <vector>
#include <iostream>

#include "AST.h"

using namespace std;

Node::Node(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = data2;
}

LITERAL::LITERAL(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}


FCALL::FCALL(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}


FDECL::FDECL(string type, string value, vector<AbstractNode> data, vector<AbstractNode> data2) {
  _type = type;
  _value = value;
  _data = data;
  body = data2;
}

string LITERAL::codegen() {
  return _value;
}

string FCALL::codegen() {
  string code = _value + "(";
  for (int i = 0; i < _data.size(); i++) {
    code += _data[i]._LIT._value;
  }
  code += ")";
  return code + ";";
}

string FDECL::codegen() {
  string code = "fun " + _value + "(";
  for (int i = 0; i < _data.size(); i++) {
    code += _data[i]._LIT.codegen();
    if (i != _data.size() - 1) {
      // code += ", ";
    }
  }
  code += ") {\n";
  for (int i = 0; i < body.size(); i++) {
    code += "  " + body[i]._FC.codegen() + "";

  }
  return code + "\n}";
}
