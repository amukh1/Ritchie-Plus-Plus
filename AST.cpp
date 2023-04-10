#include <string>
#include <vector>
#include <iostream>

#include "AST.h"

using namespace std;

Node::Node(string type, string value, vector<Node*> data) {
  _type = type;
  _value = value;
  _data = data;
  // _data2 = data2;
}

LITERAL::LITERAL(string type, string value, vector<Node*> data) {
  _type = type;
  _value = value;
  _data = data;
  // _data2 = {};
}

FCALL::FCALL(string type, string value, vector<Node*> data) {
  _type = type;
  _value = value;
  _data = data;
  // _data2 = {};
}

FDECL::FDECL(string type, string value, vector<Node*> data, vector<Node*> data2) {
  _type = type;
  _value = value;
  _data = data;
  _data2 = data2;
}

