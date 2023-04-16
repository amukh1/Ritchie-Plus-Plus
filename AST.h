#pragma once
#include <string>
#include <vector>

using namespace std;

// union NodeTypes
// {
//   LITERAL LIT;
//   FDECL FD;
//   FCALL FC;
//   bool NUL;
//   NodeTypes() = default;
//   ~NodeTypes() = default;
// };

// struct AbstractNode
// {
//   NodeTypes node;
//   string type;
//   AbstractNode()
//   {
//     node.NUL = true;
//     type = "empty";
//     // initialize union with empty node
//     // initialize stored node type string with "empty"
//   }
// };

class AbstractNode;

class Node {
public:
  string _type;
  string _value;
  vector<AbstractNode> _data;
  // vector<Node> _data2;
  Node() = default;
  Node(string type, string value, vector<AbstractNode> data);
//   void out(string filename);
  // ~Node();
};

// class nll: public Node {
// public:
//   nll(string type, string value, vector<Node*> data);
//   // ~nll();
// };

class LITERAL: public Node {
public:
  LITERAL(string type, string value, vector<AbstractNode> data);
  LITERAL() = default;
  // ~Literal();
};

class FCALL: public Node {
public:
  FCALL(string type, string value, vector<AbstractNode> data);
  FCALL() = default;
  // ~FCALL();
};


class FDECL: public Node {
public:
  vector<AbstractNode> body;
  FDECL(string type, string value, vector<AbstractNode> data, vector<AbstractNode> data2);
  FDECL() = default;
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

class AbstractNode {
public:
  string _type;
  FDECL _FD;
  FCALL _FC;
  LITERAL _LIT;
  AbstractNode() = default;
};