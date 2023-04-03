#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "lexer.h"

using namespace std;

vector<vector<string>> regtok ={
    {"NULL", "/^\\s+/"},
    {"SEMI", "/^;/g"},
    {"NUMBER", "/^[\\d\\.]+/"},
    {"WORD", "/^[a-zA-Z][a-zA-Z\\d\\.]*/"},
};


// fuck c++, why does it take 9 lines for a strcpy??? :middle_finger:
Lexer::Lexer(string filename)
{
    Lexer::_cursor = 0;
    Lexer::tokenRegex = regtok;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        Lexer::_string += (line + "\n");
    }
}

void Lexer::printTokens() {
    string out = "";

    for(int i = 0; i < Lexer::_tokens.size(); i++) {
        out += (Lexer::_tokens[i][0] + ":" + (Lexer::_tokens[i][1]) + "\n");
    }

    cout << out << endl;
}

// they are really gonna make me do it from scratch, huh?
void Lexer::tokenize(string str) {
    // while(true) {
    //     bool eof = Lexer::advance();
    //     if(eof) {
    //         break;
    //     }
    // }
cout << "help.. code.." << endl;
    // implement tokenization using regex, rather than iteration:
    for(int i = 0; i < Lexer::tokenRegex.size(); i++) {
        cout << "help.. code.." << endl;
        if(regex_search(str, regex(Lexer::tokenRegex[i][1]))) {
            cout << "a, regex, passed" << endl;
        }
    }
}


// uh oh.. regular expression? where's waldo??
// bool Lexer::advance() {
//     if((Lexer::_string.size() - 1) == Lexer::_cursor) {
//         return true;
//     }else {
//         int i = Lexer::_cursor;
//         char c = Lexer::_string.at(i);
//         std::string s(1, c);
//         // vector<string> val = {"CHAR", s};
//         // Lexer::_tokens.push_back(val);
//         if(regex_match(s, regex("/^\\s+/"))) {
//             cout << "whitespace" << endl;
//         }
//         Lexer::_cursor++;
//         return false;
//     }
// }