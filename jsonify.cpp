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
    out.append("\"_ftype\":\"" + node._type + "\",");
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
    out.append("\"type\":\"" + node._type + "\",");
    if(node._type == "STRING") { out.append("\"_value\":" + node._value + ","); } else
    out.append("\"_value\":\"" + node._value + "\",");
    out.append("\"_data\":[");
    for (int i = 0; i < node._data.size(); i++) {
      out.append(stringify(node._data[i]));
      if(i != node._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  } else if (ast._type == "RET") {
    RET ret = ast._RET;
    out.append("\"value\":" + ret._value + ",");
    out.append("\"type\":\"" + ret.ctype + "\"");
  }else if (ast._type == "IMP") {
    IMP imp = ast._IMP;
    out.append("\"value\":" + imp._value);
  }else if(ast._type == "ASM") {
    ASM asm_ = ast._ASM;
    out.append("\"value\":" + asm_._value + "");
  }else if(ast._type == "ASSIGN") {
    ASSIGN assign = ast._ASSIGN;
    out.append("\"name\":\"" + assign._type + "\",");
    if(assign._data[0]._LIT._type == "STRING") { out.append("\"value\":" + assign._value ); } else
    out.append("\"value\":\"" + assign._value + "\"");
  }else if(ast._type == "REFER") {
    REFER refer = ast._REFER;
    if(refer._data[0]._LIT._type == "STRING") { out.append("\"value\":" + refer._value); } else
    out.append("\"value\":\"" + refer._value + "\"");
  }else if(ast._type == "DEREF") {
    DEREF deref = ast._DEREF;
    if(deref._data[0]._LIT._type == "STRING") { out.append("\"value\":" + deref._value); } else
    out.append("\"value\":\"" + deref._value + "\"");
  }else if(ast._type == "IE") {
    IE ie = ast._IE;
    out.append("\"type\":\"" + ie._type + "\",");
    out.append("\"value\":\"" + ie._value + "\"");
  }else if(ast._type == "OPP") {
    OPP opp = ast._OPP;
    out.append("\"type\":\"" + opp._type + "\",");
    out.append("\"value\":\"" + opp._value + "\",");
    out.append("\"operands\":[");
    for (int i = 0; i < opp._data.size(); i++) {
      out.append(stringify(opp._data[i]));
      if(i != opp._data.size() - 1) {
        out.append(",");
      }
    }
    out.append("]");
  }else if(ast._type == "PNTR") {
    out.append("\"type\":\"" + ast._PNTR._type + "\",");
    out.append("\"value\":\"" + ast._PNTR._value + "\"");
  }else if(ast._type == "LCLASS") {
    out.append("\"type\":\"" + ast._LCLASS._type + "\",");
    out.append("\"value\":\"" + ast._LCLASS._value + "\"");
  }else if(ast._type == "LCLDEF") {
    out.append("\"type\":\"" + ast._LCLDEF._type + "\",");
    out.append("\"value\":\"" + ast._LCLDEF._value + "\"");
  }


  out.append("}");
  return out;
}

string stringifyv(vector<AbstractNode> ast) {
  string out = "[";
  for (int i = 0; i < ast.size(); i++) {
    out.append(stringify(ast[i]));
    if(i != ast.size() - 1) {
      out.append(",");
    }
  }
  return out + "]";
}