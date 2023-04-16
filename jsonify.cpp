#include <vector>
#include <iostream>
#include "AST.h"

using namespace std;

string stringify(AbstractNode ast) {
  string out = "{";
  out.append("_type:" + ast._type + ",");
  if(ast._type == "FDECL") {
    FDECL node = ast._FD;
    out.append("_value:" + node._value + ",");
    out.append("_data:[");
    for (int i = 0; i < node._data.size(); i++) {
      out.append(stringify(node._data[i]));
      if(i != node._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("],");
    out.append("_data2:[");
    for (int i = 0; i < node._data2.size(); i++) {
      out.append(stringify(node._data2[i]));
      if(i != node._data2.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  }else if(ast._type == "FCALL") {
    FCALL node = ast._FC;
    out.append("_value:" + node._value + ",");
    out.append("_data:[");
    for (int i = 0; i < node._data.size(); i++) {
      out.append(stringify(node._data[i]));
      if(i != node._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  }else if(ast._type == "LITERAL") {
    LITERAL node = ast._LIT;
    out.append("_value:" + node._value + ",");
    out.append("_data:[");
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
//     out += ast[i]._type + " " + ast[i]._value + " " + stringify(ast[i]._data) + " " + stringify(ast[i]._data2);
//   }
//   return out;
// }