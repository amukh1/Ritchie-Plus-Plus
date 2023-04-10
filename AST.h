#pragma once
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  string _type;
  string _value;
  vector<Node*> _data;
  // vector<Node> _data2;
  Node() = default;
  Node(string type, string value, vector<Node*> data);
//   void out(string filename);
  // ~Node();
};

class LITERAL: public Node {
public:
  LITERAL(string type, string value, vector<Node*> data);
  // ~Literal();
};

class FCALL: public Node {
public:
  FCALL(string type, string value, vector<Node*> data);
  // ~FCALL();
};


class FDECL: public Node {
public:
  vector<Node*> _data2;
  FDECL(string type, string value, vector<Node*> data, vector<Node*> data2);
  // ~FDECL();
};

// class ExprOpen: public Node {
// public:
//   ExprOpen(string type, string value, vector<Node> data);
//   // ~ExprOpen();
// };

// class ExprClosed: public Node {
// public:
//   ExprClosed(string type, string value, vector<Node> data);
//   // ~ExprClose();
// };