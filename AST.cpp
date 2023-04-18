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

RET::RET(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}

string RET::codegen() { return "return " + _value + ";"; }


IMP::IMP(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}

string IMP::codegen() { return "#include " + _value; }


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
  string code = "\n" + rtype + " " + _value + "(";
  for (int i = 0; i < _data.size(); i++) {
    code += _data[i]._LIT.ctype + " " + _data[i]._LIT.codegen();
    if (i != _data.size() - 1) {
      code += ", ";
    }
  }
  code += ") {\n\n";
  for (int i = 0; i < body.size(); i++) {
    if(body[i]._type == "RET"){
      code += "  " + body[i]._RET.codegen() + "\n";
    }else if(body[i]._type == "FCALL"){
    code += "  " + body[i]._FC.codegen() + "\n";
    }else if(body[i]._type == "IMP"){
    code += "  " + body[i]._IMP.codegen() + "\n";
    }

  }
  return code + "\n}";
}
