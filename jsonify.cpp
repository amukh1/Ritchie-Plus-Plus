#include <vector>
#include <iostream>
#include "AST.h"

using namespace std;

string stringify(AbstractNode ast) {
  string out = "{";
  out.append("\"_type\":\"" + ast._type + "\",");
  if(ast._type == "FDECL") {
    FDECL node = ast._FD;
    out.append("\"_value\":\"" + node._value + "\",");
    out.append("\"_data\":[");
    for (int i = 0; i < node._data.size(); i++) {
      out.append(stringify(node._data[i]));
      if(i != node._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("],");
    out.append("\"body\":[");
    for (int i = 0; i < node.body.size(); i++) {
      out.append(stringify(node.body[i]));
      if(i != node.body.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  }else if(ast._type == "FCALL") {
    FCALL node = ast._FC;
    // cout << node._value << endl;
    out.append("\"_value\":\"" + node._value + "\",");
    out.append("\"_data\":[");
    for (int i = 0; i < node._data.size(); i++) {
      out.append(stringify(node._data[i]));
      if(i != node._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  }else if(ast._type == "LITERAL") {
    LITERAL node = ast._LIT;
    // cout << node._type + ":" + node._value << endl;
    if(node._type == "LITERAL") { out.append("\"_value\":" + node._value + ","); } else
    out.append("\"_value\":\"" + node._value + "\",");
    out.append("\"_data\":[");
    for (int i = 0; i < node._data.size(); i++) {
      out.append(stringify(node._data[i]));
      if(i != node._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  }


  out.append("}");
  return out;
}

// string stringifyf(vector<AbstractNode> ast) {
//   string out = "";
//   for (int i = 0; i < ast.size(); i++) {
//     out += ast[i]._type + " " + ast[i]._value + " " + stringify(ast[i]._data) + " " + stringify(ast[i].body);
//   }
//   return out;
// }