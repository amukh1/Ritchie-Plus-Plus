#pragma once
#include <string>
#include <vector>

// #include "AST.h"

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

class x86 {
public:
  string type = "o";
  string out = "section	.text\n        global _start\n    _start:\n call main \n call end";
  string data = "\nsection .data\n\n NEWLINE db 10\n";
  string bss = "\nsection .bss\n\n";
  vector<string> vars;
  int constants = 0;
  void add(string addit);
  string constant(string ctype, string cvalue);
  string variable(string vtype, string vname, string vvalue);
  void sout();
};

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

class LITERAL : public Node {
public:
  string ctype;
  LITERAL(string type, string value, vector<AbstractNode> data);
  LITERAL() = default;
  // ~Literal();
  string codegen(string otype, x86* a);
};

class FCALL : public Node {
public:
  FCALL(string type, string value, vector<AbstractNode> data);
  FCALL() = default;
  // ~FCALL();
  string codegen(string otype, x86* a);
};

class FDECL : public Node {
public:
  vector<AbstractNode> body;
  string rtype;
  FDECL(string type, string value, vector<AbstractNode> data,
        vector<AbstractNode> data2);
  FDECL() = default;
  // ~FDECL();
  string codegen(string otype, x86* a);
};

class RET : public Node {
public:
  string ctype;
  RET(string type, string value, vector<AbstractNode> data);
  RET() = default;
  // ~FCALL();
  string codegen(string otype, x86* a);
};

class IMP : public Node {
public:
  IMP(string type, string value, vector<AbstractNode> data);
  IMP() = default;
  // ~FCALL();
  string codegen(string otype, x86* a);
};

class ASM : public Node {
public:
  ASM(string type, string value, vector<AbstractNode> data);
  ASM() = default;
  // ~FCALL();
  string codegen(string otype, x86* a);
};

class ASSIGN : public Node {
public:
  ASSIGN(string type, string value, vector<AbstractNode> data);
  ASSIGN() = default;
  // ~FCALL();
  string codegen(string otype, x86* a);
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
  RET _RET;
  IMP _IMP;
  ASM _ASM;
  ASSIGN _ASSIGN;
  AbstractNode() = default;
};