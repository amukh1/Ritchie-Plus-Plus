#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "AST.h"

using namespace std;

Node::Node(string type, string value, vector<Node> data) {
  _type = type;
  _value = value;
  _data = data;
}

// Literal::Literal(string type, string value, vector<Node> data) {
//   _type = type;
//   _value = value;
//   _data = data;
// }

// FCALL::FCALL(string type, string value, vector<Node> data) {
//   _type = type;
//   _value = value;
//   _data = data;
// }

