#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

IMP::IMP(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}

FDECL::FDECL(string type, string value, vector<AbstractNode> data,
             vector<AbstractNode> data2) {
  _type = type;
  _value = value;
  _data = data;
  body = data2;
}

ASM::ASM(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}

ASSIGN::ASSIGN(string type, string value, vector<AbstractNode> data) {
  _type = type;
  _value = value;
  _data = data;
  // body = {};
}

void x86::add(string addit) { out.append(addit); }

void x86::sout() { bss.append(out.append(data)); }

string x86::constant(string ctype, string cvalue) {
  data += "RPP_CONSTANT_" + to_string(constants) + " db " + cvalue + ", 0\n";
  constants++;
  return "RPP_CONSTANT_" + to_string(constants - 1);
}

string x86::variable(string vtype, string vname, string vvalue) {
  // a->constant(_data[i]._LIT.ctype, _data[i]._LIT._value)
  if (!(find(vars.begin(), vars.end(), vname) != vars.end())) {
        vars.push_back(vname);
        bss.append(vname + ": resb 4\n");
    }
    // return "mov eax, " + vvalue + "\nmov [" + vname + "], eax" + "\n";
    if(vtype == "STRING") {
      return "mov eax, " + constant(vtype, vvalue) + "\nmov [" + vname + "], eax" + "\n";
    }else {
      return "mov eax, " + vvalue + "\nmov [" + vname + "], eax" + "\n";
    }
}