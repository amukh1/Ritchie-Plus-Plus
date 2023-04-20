#include <iostream>
#include <string>
#include <vector>

#include "AST.h"

using namespace std;

string RET::codegen(string otype, x86* a) {
  if (otype == "c") {
    return "return " + _value + ";";
  } else if (otype == "o") {
    return "  mov " + _value + ", eax\n";
  } else
    return "";
}

string IMP::codegen(string otype, x86* a) {
  if (otype == "c") {
    return "#include " + _value;
  } else if (otype == "o") {
    return "assembly import " + _value + "\n";
  } else
    return "";
}

string LITERAL::codegen(string otype, x86* a) {
  if (otype == "c") {
    return _value;
  } else if (otype == "o") {
    return _value;
  } else
    return "";
}

string FCALL::codegen(string otype, x86* a) {
  if (otype == "c") {
    string code = _value + "(";
    for (int i = 0; i < _data.size(); i++) {
      code += _data[i]._LIT._value;
    }
    code += ")";
    return code + ";";
  } else if (otype == "o") {
    for (int i = 0; i < _data.size(); i++) {
      a->add("  push " + _data[i]._LIT._value + "\n");
    }
    a->add("  call " + _value + "\n\n");
    // a->out.app;
    return "";
  } else
    return "";
}
string FDECL::codegen(string otype, x86* a) {
  if (otype == "c") {
    string code = "\n" + rtype + " " + _value + "(";
    for (int i = 0; i < _data.size(); i++) {
      code += _data[i]._LIT.ctype + " " + _data[i]._LIT.codegen(otype, a);
      if (i != _data.size() - 1) {
        code += ", ";
      } else
        return "";
    }
    code += ") {\n\n";
    for (int i = 0; i < body.size(); i++) {
      if (body[i]._type == "RET") {
        code += "  " + body[i]._RET.codegen(otype,a) + "\n";
      } else if (body[i]._type == "FCALL") {
        code += "  " + body[i]._FC.codegen(otype,a) + "\n";
      } else if (body[i]._type == "IMP") {
        code += "  " + body[i]._IMP.codegen(otype,a) + "\n";
      }
    }
    return code + "\n}";
  } else if (otype == "o") {
    a->add("\n" + _value +":\n");
    string code = "";
    for (int i = 0; i < body.size(); i++) {
      if (body[i]._type == "RET") {
        code +=   body[i]._RET.codegen(otype,a);
      } else if (body[i]._type == "FCALL") {
        code +=   body[i]._FC.codegen(otype,a);
      } else if (body[i]._type == "IMP") {
        code +=   body[i]._IMP.codegen(otype,a);
      }
    }
    a->add(code);
    return code;
  } else
    return "";
}
