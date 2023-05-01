#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "parser.h"

using namespace std;

Parser::Parser(vector<vector<string>> tokens) { _tokens = tokens; }

void Parser::printTokens() {
  for (int i = 0; i < _tokens.size(); i++) {
    cout << _tokens[i][0] << " " << _tokens[i][1] << endl;
  }
}

void Parser::parse() {
  for (int i = 0; i < _tokens.size(); i++) {
    // just for testing, kicks n giggles
    // function call
    if (_tokens.size() == 1) {
      LITERAL lit(_tokens[i][0], _tokens[i][1], {});
      AbstractNode abnode;
      abnode._type = "LITERAL";
      abnode._LIT = lit;
      _ast.push_back(abnode);
      break;
    }else if(_tokens[i][0] == "WORD" && _tokens[i][1] == "ASM" ||  _tokens[i][1] == "asm" && _tokens[i+1][0] == "O-PAREN") {
      string asmcode = _tokens[i+2][1];
      ASM asmnode("ASM", asmcode, {});
      AbstractNode abnode;
      abnode._type = "ASM";
      abnode._ASM = asmnode;
      _ast.push_back(abnode);
      i+=4;
    }else if (_tokens[i][0] == "WORD" && _tokens[i + 1][0] == "O-PAREN") {
      // cout << "Function call: " << _tokens[i][1] << "; ";
      string name = _tokens[i][1];
      vector<AbstractNode> args = {};
      i += 2;
      while (_tokens[i][0] != "C-PAREN") {
        if (_tokens[i][0] == "COMMA") {
          i++;
          continue;
        }
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        // args.push_back(Node("LITERAL", _tokens[i][1], {}));
        LITERAL lit(_tokens[i][0], _tokens[i][1], {});
        struct AbstractNode abnode;
        abnode._type = "LITERAL";
        abnode._LIT = lit;

        args.push_back(abnode);
        i++;
      }
      FCALL fcall("FCALL", name, args);
      AbstractNode node;
      node._type = "FCALL";
      node._FC = fcall;
      _ast.push_back(node);
      i++;
      // cout << "Parsed an FCALL Node" << endl;
    }
    // function declaration + definition
    else if (_tokens[i][0] == "WORD" && _tokens[i + 1][0] == "WORD" && _tokens[i + 2][0] == "O-PAREN" &&
             _tokens[i][1] == "func") {
      vector<string> name = _tokens[i + 1];
      // if(name[1] == "main") name[1] = "_start";
      // string rtype = _tokens[i + 1][1];
      // cout << "Function declaration: " << _tokens[i][1] << "; ";
      vector<AbstractNode> args = {};
      i += 3;
      int parens = 1;
      while (parens > 0) {
        // cout << _tokens[i][0] << endl;
        if (_tokens[i][0] == "COMMA") {
          i++;
          continue;
        }
        if (_tokens[i][0] == "O-PAREN")
          parens++;
        if (_tokens[i][0] == "C-PAREN") {
          parens--;
          break;
        }
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        LITERAL nod(_tokens[i][0], _tokens[i][1], {});
        // nod.ctype = _tokens[i][1];
        nod.ctype = "DROPPED SUPPORT FOR C";
        AbstractNode abnode;
        abnode._type = "LITERAL";
        abnode._LIT = nod;
        args.push_back(abnode);
        i += 1;
      }
      i += 2;
      vector<vector<string>> body = {};
      while (_tokens[i][0] != "C-BRACE") {
        // cout << to_string(args.size()) << ": " << _tokens[i][1] << ";";
        body.push_back(_tokens[i]);
        i++;
      }
      // parse body
      Parser par(body);
      par.parse();
      FDECL fdecl("FDECL", name[1], args, par._ast);
      // fdecl.rtype = rtype;
      fdecl.rtype = "DROPPED SUPPORT FOR C";
      AbstractNode abnode;
      abnode._type = "FDECL";
      abnode._FD = fdecl;
      _ast.push_back(abnode);
      i+=2;
      // par.out("par.ast");

      // cout << "Parsed an FDECL Node" << endl;
    } else if (_tokens[i][0] == "WORD" && _tokens[i][1] == "return") {
      RET ret("RET", _tokens[i + 1][1], {});
      // ret.ctype = _tokens[i + 1][1];
      ret.ctype = "DROPPED SUPPORT FOR C";
      AbstractNode abnode;
      abnode._type = "RET";
      abnode._RET = ret;
      _ast.push_back(abnode);
      i += 2;
    } else if (_tokens[i][0] == "WORD" && _tokens[i][1] == "import" && _tokens[i + 1][0] == "STRING") {
      if(_tokens[i+1][0] == "STRING") {
      IMP imp("IMP", _tokens[i + 1][1], {});
      AbstractNode abnode;
      abnode._type = "IMP";
      abnode._IMP = imp;
      _ast.push_back(abnode);
      }else {
        // type is "WORD"
        EXTERNAL ext("EXTERNAL", _tokens[i+1][1], {});
        AbstractNode abnode;
        abnode._type = "EXTERNAL";
        abnode._EXTERNAL = ext;
        _ast.push_back(abnode);
      }
      i += 2;
    }else if(_tokens[i][0] == "WORD" && _tokens[i+1][0] == "WORD" && _tokens[i][1] == "var") {
      string name = _tokens[i+1][1];
      string value = _tokens[i+3][1];
      string t = _tokens[i+3][0];
      // int oli = i;

      vector<vector<string>> toks = {};
      i+=3;
      while(_tokens[i][0] != "SEMI") {
        toks.push_back(_tokens[i]);
        i++;
      }
      // parse tokens
      Parser par(toks);
      par.parse();
      // cout << par._ast[0]._type << endl;

      LITERAL lit(t, value, par._ast);
      AbstractNode abnode1;
      abnode1._type = "LITERAL";
      abnode1._LIT = lit;
      ASSIGN var(name, value, {abnode1});
      AbstractNode abnode;
      abnode._type = "ASSIGN";
      abnode._ASSIGN = var;
      _ast.push_back(abnode);
      // cout << oli - i << endl;
      // i+=4;
    }else if(_tokens[i][0] == "WORD" && _tokens[i+2][0] == "WORD" && _tokens[i][1] == "var" && _tokens[i+1][0] == "AMP") {
      string name = _tokens[i+2][1];
      string value = _tokens[i+4][1];
      LITERAL lit(_tokens[i+4][0], value, {});
      AbstractNode abnode1;
      abnode1._type = "LITERAL";
      abnode1._LIT = lit;
      REFER var(name, value, {abnode1});
      AbstractNode abnode;
      abnode._type = "REFER";
      abnode._REFER = var;
      _ast.push_back(abnode);
      i+=5;
    }else if(_tokens[i][0] == "WORD" && _tokens[i+2][0] == "WORD" && _tokens[i][1] == "var" && _tokens[i+1][0] == "STAR") {
      string name = _tokens[i+2][1];
      string value = _tokens[i+4][1];
      LITERAL lit(_tokens[i+4][0], value, {});
      AbstractNode abnode1;
      abnode1._type = "LITERAL";
      abnode1._LIT = lit;
      DEREF var(name, value, {abnode1});
      AbstractNode abnode;
      abnode._type = "DEREF";
      abnode._DEREF = var;
      _ast.push_back(abnode);
      i+=5;
    }else if(_tokens[i][0] == "WORD" && _tokens[i][1] == "import" || _tokens[i][1] == "export" && _tokens[i+1][0] == "WORD") {
      // cout << "here" << endl;
      IE ie(_tokens[i][1], _tokens[i+1][1], {});
      AbstractNode abnode;
      abnode._type = "IE";
      abnode._IE = ie;
      _ast.push_back(abnode);
      i+=2;
    }else if(_tokens[i+1][0] == "OPP"){
      // operation
      string op = _tokens[i+1][1];
      LITERAL A(_tokens[i][0], _tokens[i][1], {});
      LITERAL B(_tokens[i+2][0], _tokens[i+2][1], {});

      AbstractNode AA;
      AbstractNode BB;

      AA._type = "LITERAL";
      AA._LIT = A;

      BB._type = "LITERAL";
      BB._LIT = B;

      OPP opp(op, "null", {AA, BB});
      AbstractNode abnode;
      abnode._type = "OPP";
      abnode._OPP = opp;
      _ast.push_back(abnode);
      i+=2;
    }else {
      // make it a literal
      LITERAL lit(_tokens[i][0], _tokens[i][1], {});
      AbstractNode abnode;
      abnode._type = "LITERAL";
      abnode._LIT = lit;
      _ast.push_back(abnode);
      // i++;
      // cout << "Error: " << _tokens[i][0] << " " << _tokens[i][1] << " at " << to_string(i) << endl;
    }
    // cout << "Token:" << _tokens[i][0] << " " << _tokens[i][1] << endl;
  }
}
