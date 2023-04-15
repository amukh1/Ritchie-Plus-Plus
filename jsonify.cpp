#include <vector>
#include <iostream>
#include "AST.h"

using namespace std;

string stringify(AbstractNode ast) {
  string out = "{";
  out.append(ast._type + ":");
  return out;
}

string stringifyf(vector<AbstractNode> ast) {
  string out = "";
  for (int i = 0; i < ast.size(); i++) {
    out += ast[i]._type + " " + ast[i]._value + " " + stringify(ast[i]._data) + " " + stringify(ast[i]._data2);
  }
  return out;
}