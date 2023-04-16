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
