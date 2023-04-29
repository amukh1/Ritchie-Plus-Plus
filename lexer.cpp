#include "lexer.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

/* 
tokens = [
  [/^\s+/, null],
  // semicolon
  [/^;/, 'SEMI'],
  // comments
  [/^\/\/.*\/, null],
  // multiline comments
  [/^\/\*[\s\S]*?\*\//, null],
  [/^\.\./, 'CONCAT'],
  [/^[\d\.]+/, 'NUMBER'],
  // literals: string
  [/^"[^"]*"|^'[^']*'/, 'STRING'],
  // commas
  // [/^\,/,'COMMA'],
  // paren
  [/^\(/, 'O-PAREN'],
  [/^\)/, 'C-PAREN'],
  // brackets
  [/^\{/, 'O-BRACE'],
  [/^\}/, 'C-BRACE'],
  [/^\[/, 'O-BRACK'],
  [/^\]/, 'C-BRACK'],
  [/^\!/, 'EXPI'],
  [/^:/, 'COLON'],

    [/^>/, 'GRT'],
  [/^</, 'LST'],

  [/^=/, 'DECLARATION'],
  [/^==/, 'EQUALITY'],
  [/^\,/, 'COMMA'],
  [/^\+/, 'ADD'],
  [/^-/, 'SUB'],
  [/^\*\/, 'MULT'],
  [/^\//, 'DIV'],
  // words/vars
  [/^[a-zA-Z][a-zA-Z\d\.]*\/, 'WORD'],
]
*/

vector<vector<string>> regtok = {
    {"COMMENT", "^\\/\\/.*\\/"},
    {"MCOMMENT", "^\\/\\*[\\s\\S]*?\\*\\n"}, // 24
    {"NULL", "^\\s+"}, // 0
    {"SEMI", "^;"},
    {"NUMBER", "^[\\d\\.]+"}, // 2
    {"WORD", "^[a-zA-Z][a-zA-Z\\d\\.]*"},
    {"STRING", "^\"[^\"]*\"|^'[^']*'"}, // 4
    {"O-PAREN", "^\\("},
    {"C-PAREN", "^\\)"}, // 6
    {"O-BRACE", "^\\{"},
    {"C-BRACE", "^\\}"}, // 8
    {"O-BRACK", "^\\["},
    {"C-BRACK", "^\\]"}, // 10
    {"EXPI", "^\\!"},
    {"COLON", "^:"}, // 12
    {"GRT", "^>"},
    {"LST", "^<"}, // 14
    {"DECLARATION", "^="},
    {"EQUALITY", "^=="}, // 16
    {"COMMA", "^,"},
    {"ADD", "^\\+"}, // 18
    {"SUB", "^-"},
    {"STAR", "^\\*"}, // 20
    {"DIV", "^\\/"},
    {"CONCAT", "^\\.\\."}, // 22
    {"AMP", "^&"}, // 22
};

// screw c++, why does it take 9 lines for a strcpy??? :m_finger:
// ^ L

Lexer::Lexer(string filename) {
  Lexer::_cursor = 0;
  Lexer::tokenRegex = regtok;
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    Lexer::_string += (line + "\n");
  }
}

void Lexer::printTokens() {
  string out = "";

  for (int i = 0; i < Lexer::_tokens.size(); i++) {
    out += (Lexer::_tokens[i][0] + ":" + (Lexer::_tokens[i][1]) + "\n");
  }

  cout << out << endl;
}

// they are really gonna make me do it from scratch, huh?
// no ^ :D

void Lexer::tokenize() {
  string str = Lexer::_string;
  string s = Lexer::_string;
  while (s != "") {
    for (auto x : regtok) {
      regex regexp(x[1]);
      smatch m;
      regex_search(s, m, regexp);
      if (m.size() != 0) {
        string mz = m[0];
        // cout << "token! " << x[0] << ": " << mz << endl;
        s = s.substr(mz.size(), str.size() - mz.size());
        if (x[0] != "NULL")
          Lexer::_tokens.push_back({x[0], mz});
      }
    }
  }
}

// uh oh.. regular expression? where's waldo??
// ^ up there buddy

/*
why subject myself to this torture?

bool Lexer::advance() {
    if((Lexer::_string.size() - 1) == Lexer::_cursor) {
        return true;
    }else {
        int i = Lexer::_cursor;
        char c = Lexer::_string.at(i);
        std::string s(1, c);
        // vector<string> val = {"CHAR", s};
        // Lexer::_tokens.push_back(val);
        if(regex_match(s, regex("/^\\s+/"))) {
            cout << "whitespace" << endl;
        }
        Lexer::_cursor++;
        return false;
    }
}
*/