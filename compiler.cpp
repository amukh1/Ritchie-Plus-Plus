#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "AST.h"

using namespace std;

string stdio = "\nprintln: \n\
pop edi \n\
pop edx \n\
pop ecx \n\
mov ebx, 1 \n\
mov eax, 4 \n\
int 0x80 \n\
\n\
mov edx, 1 \n\
mov ecx, NEWLINE \n\
mov ebx, 1 \n\
mov eax, 4 \n\
int 0x80 \n\
\n\
push edi \n\
ret \n\
\n\
print: \n\
pop edi \n\
pop edx \n\
pop ecx \n\
mov ebx, 1 \n\
mov eax, 4 \n\
int 0x80 \n\
\n\
mov eax, 0 \n\
push edi \n\
ret\n";

string stdlib = "\nend: \n\
mov eax, 1 \n\
int 0x80 \n";

string RET::codegen(string otype, x86* a) {
  if (false) {
    return "return " + _value + ";";
  } else if (true) {
    return "  mov eax, " + _value + "\n   ret\n";
  } else
    return "";
}

string IMP::codegen(string otype, x86* a) {
  if (false) {
    return "#include " + _value;
  } else if (true) {
    // get asm from package folder
    // fstream file;
    // cout << "./packages/" + _value.erase(0,1).erase(_value.size()-1,1) + ".asm" << endl;
    // file.open("./packages/" + _value.erase(0,1).erase(_value.size()-1,1) + ".asm");
    // string line;
    // while (getline(file, line)) {
    //   cout << line << endl;
    //   a->add(line + "\n");
    // }
    // file.close();
    if(_value == "\"stdio\"") a->add(stdio);
    if(_value == "\"stdlib\"") a->add(stdlib);
    return "\n";
  } else
    return "";
}

string LITERAL::codegen(string otype, x86* a) {
  if (false) {
    return _value;
  } else if (true) {
    return _value;
  } else
    return "";
}

string FCALL::codegen(string otype, x86* a) {
  if (false) {
    string code = _value + "(";
    for (int i = 0; i < _data.size(); i++) {
      code += _data[i]._LIT._value;
    }
    code += ")";
    return code + ";";
  } else if (true) {
    for (int i = 0; i < _data.size(); i++) {
      if(_data[i]._LIT._value != ","){
      if(_data[i]._LIT._type == "STRING")
      a->add("  mov eax, " +  a->constant(_data[i]._LIT.ctype, _data[i]._LIT._value) +  "\n  push eax\n");
      else if(_data[i]._LIT._type == "WORD")
      a->add("  mov eax, [" + _data[i]._LIT._value + "]\n  push eax\n");
      else if(_data[i]._LIT._type == "NUMBER")
      a->add("  mov eax, " +  _data[i]._LIT._value +  "\n  push eax\n");
      }
    }
    a->add("  call " + _value + "\n\n");
    // a->out.app;
    return "eax";
  } else
    return "";
}

string ASM::codegen(string otype, x86* a) {
  a->add(_value.erase(0,1).erase(_value.size()-1, 1) + "\n");
  return "";
}

string ASSIGN::codegen(string otype, x86* a) {
  // cout << _data[0]._LIT._data[0]._type << endl;
    if(_data[0]._LIT._data[0]._type == "LITERAL")
    a->add(a->variable(_data[0]._LIT._type, _type, _value));
    else if(_data[0]._LIT._data[0]._type == "FCALL"){
      // must be a function call

      a->add(a->variable(_data[0]._LIT._type, _type, _data[0]._LIT._data[0]._FC.codegen(otype,a)));
    }else if(_data[0]._LIT._data[0]._type == "OPP") {
      a->add(a->variable(_data[0]._LIT._type, _type, _data[0]._LIT._data[0]._OPP.codegen(otype,a)));
    }
    return "";
}

string REFER::codegen(string otype, x86* a) {
  a->add(a->point(_data[0]._LIT._type, _type, _value));
  return "";
}

string DEREF::codegen(string otype, x86* a) {
  a->add(a->deref(_data[0]._LIT._type, _type, _value));
  return "";
}

string IE::codegen(string otype, x86* a) {
  // cout << "heard" << endl;
  if(_type == "import") {
    a->add("extern " + _value + "\n");
  }else {
    a->add("global " + _value + "\n");
  }
  return "";
}

string OPP::codegen(string otype, x86* a) {
  a->add("mov eax, " + _data[0]._LIT._value + "\n");
  if(_type == "+") a->add("add eax, " + _data[1]._LIT._value + "\n");
  if(_type == "-") a->add("sub eax, " + _data[1]._LIT._value + "\n");
  if(_type == "*") a->add("mul eax, " + _data[1]._LIT._value + "\n");
  if(_type == "/") a->add("div eax, " + _data[1]._LIT._value + "\n");
  return "eax";
}



string FDECL::codegen(string otype, x86* a) {
  if (false) {
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
        // code += "  " + body[i]._FC.codegen(otype,a) + "\n";
        body[i]._FC.codegen(otype,a);
      } else if (body[i]._type == "IMP") {
        code += "  " + body[i]._IMP.codegen(otype,a) + "\n";
      }else if(body[i]._type == "ASM"){
        code += "  " + body[i]._ASM.codegen(otype,a) + "\n";
      }
    }
    return code + "\n}";
  } else if (true) {
    if(_value == "main") a->add("global _start\n    _start:\n call main \n mov eax, 1\n int 0x80");
    a->add("\n" + _value +":\n");
    string code = "";
    for (int i = 0; i < body.size(); i++) {
      if(body[i]._type == "ASSIGN"){
        code +=   body[i]._ASSIGN.codegen(otype,a);
      }else if (body[i]._type == "RET") {
        code +=   body[i]._RET.codegen(otype,a);
      } else if (body[i]._type == "FCALL") {
        // code +=   body[i]._FC.codegen(otype,a);
        body[i]._FC.codegen(otype,a);
      } else if (body[i]._type == "IMP") {
        code +=   body[i]._IMP.codegen(otype,a);
      }else if(body[i]._type == "ASM"){
        code +=   body[i]._ASM.codegen(otype,a);
      }else if(body[i]._type == "REFER"){
        code +=   body[i]._REFER.codegen(otype,a);
      }else if(body[i]._type == "DEREF"){
        code +=   body[i]._DEREF.codegen(otype,a);
      }else if(body[i]._type == "IE"){
        code +=   body[i]._IE.codegen(otype,a);
      }
    }
    a->add(code);
    return code;
  } else
    return "";
}