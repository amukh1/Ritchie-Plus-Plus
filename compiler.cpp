#include <iostream>
#include <string>
#include <vector>

#include "AST.h"

using namespace std;

string RET::codegen(string otype) {
  if (otype == "c") {
    return "return " + _value + ";";
  } else if (otype == "o") {
    return "assembly return";
  } else
    return "";
}

string IMP::codegen(string otype) {
  if (otype == "c") {
    return "#include " + _value;
  } else if (otype == "o") {
    return "assembly import";
  } else
    return "";
}

string LITERAL::codegen(string otype) {
  if (otype == "c") {
    return _value;
  } else if (otype == "o") {
    return "assembly literal";
  } else
    return "";
}

string FCALL::codegen(string otype) {
  if (otype == "c") {
    string code = _value + "(";
    for (int i = 0; i < _data.size(); i++) {
      code += _data[i]._LIT._value;
    }
    code += ")";
    return code + ";";
  } else if (otype == "o") {
    return "assembly fcall";
  } else
    return "";
}
string FDECL::codegen(string otype) {
  if (otype == "c") {
    string code = "\n" + rtype + " " + _value + "(";
    for (int i = 0; i < _data.size(); i++) {
      code += _data[i]._LIT.ctype + " " + _data[i]._LIT.codegen(otype);
      if (i != _data.size() - 1) {
        code += ", ";
      } else
        return "";
    }
    code += ") {\n\n";
    for (int i = 0; i < body.size(); i++) {
      if (body[i]._type == "RET") {
        code += "  " + body[i]._RET.codegen(otype) + "\n";
      } else if (body[i]._type == "FCALL") {
        code += "  " + body[i]._FC.codegen(otype) + "\n";
      } else if (body[i]._type == "IMP") {
        code += "  " + body[i]._IMP.codegen(otype) + "\n";
      }
    }
    return code + "\n}";
  } else if (otype == "o") {
    return "assembly function";
  } else
    return "";
}
