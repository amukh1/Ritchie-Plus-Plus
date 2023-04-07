#include <string>
#include <vector>

using namespace std;

class Node {
public:
  string _type;
  string _value;
  vector<Node> _data;

  Node(string type, string value, vector<Node> data);
  // ~Node();
};

class Literal: public Node {
public:
  Literal(string type, string value, vector<Node> data);
  // ~Literal();
};

class FCALL: public Node {
public:
  FCALL(string type, string value, vector<Node> data);
  // ~FCALL();
};