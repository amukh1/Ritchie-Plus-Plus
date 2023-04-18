#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

#include "lexer.h"
#include "parser.h"
#include "AST.h"
#include "jsonify.h"

using namespace std;

// why is regex is c++ such a pain? :sob:
// in*
// its not that bad*

int main(int argc, char *argv[]) {
  string outtype;
  string outtyp = (string)argv[2];
  switch(outtyp[1]) {
    case 'o':
      outtype = "object";
      break;
    case 'c':
      outtype = "c";
      break;
    default:
      cout << "invalid output type" << endl;
      return 1;
  }
  string filename = "out2.json";
  ofstream file;
  file.open(filename);

  Lexer lexer(argv[1]);
  regex regexp(lexer.tokenRegex[3][1]);

  // cout << "In: " << lexer._string << endl;

  // lol 1/8th of the way there.. :gun: :me:
  lexer.tokenize();
  // cout << lexer._tokens.size() << endl;
  // lexer.printTokens();

  Parser parser(lexer._tokens);
  // cout << "parse started" << endl;
  parser.parse();
  // cout << parser._ast[0]._FD.body.size() << endl;
  string json = stringifyv(parser._ast);
  // cout << "parsing done" << endl;
  // cout << (*(FDECL*)(parser._ast[0])).body[0]->_type << endl;
  // parser.printAST();
  // parser.out("out.ast");
  // cout << ((FDECL*)(parser._ast[0]))->body.size() << endl;

  cout << "Out: " << endl << endl;
  string cgen = "";
  for(int i = 0; i < parser._ast.size(); i++) {
    // cgen.append(parser._ast[i].cgen());
    if(parser._ast[i]._type == "FDECL") {
      FDECL node = parser._ast[i]._FD;
      cgen.append(node.codegen());
    } else if(parser._ast[i]._type == "FCALL") {
      FCALL node = parser._ast[i]._FC;
      cgen.append(node.codegen());
    } else if(parser._ast[i]._type == "LITERAL") {
      LITERAL node = parser._ast[i]._LIT;
      cgen.append(node.codegen());
    } else if(parser._ast[i]._type == "RET") {
      RET node = parser._ast[i]._RET;
      cgen.append(node.codegen());
    } else if(parser._ast[i]._type == "IMP") {
      IMP node = parser._ast[i]._IMP;
      cgen.append(node.codegen());
    }
  }
  // cout << cgen << endl;

  file << json;

    ofstream file2;
  file2.open((string) argv[3] + "." + outtyp[1]);
  file2 << cgen;

  cout << "Compiled " << argv[1] << " to " << argv[3] << "." << outtyp[1] << endl;

  return 0;
}