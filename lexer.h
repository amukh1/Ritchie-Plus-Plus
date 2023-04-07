#include <string>
#include <vector>

using namespace std;

class Lexer {
public:
  string _string;
  vector<vector<string>> _tokens;
  int _cursor = 0;
  vector<vector<string>> tokenRegex;

  Lexer(string filename);
  // ~Lexer();

  void printTokens();

  void tokenize();

  bool advance();
};