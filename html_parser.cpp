#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::stack;
using std::string;
using std::stringstream;

bool parse(const string &, int &, int &);
string generateEndingTag(const string &);
bool checkTags(stack<string>, stack<string>);

void printUsage() {
  cout << "Usage: html_parser [options] <file_or_string>" << endl;
  cout << "Options:" << endl;
  cout << "  -f <filename>     Parse HTML from file." << endl;
  cout << "  -s <html_string>  Parse HTML from string." << endl;
  cout << "Example:" << endl;
  cout << "  html_parser -f example.html" << endl;
  cout << "  html_parser -s \"<html><body></body></html>\"" << endl;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printUsage();
    return 1;
  }

  string input;
  bool isFileInput = false;

  if (string(argv[1]) == "-f") {
    // File input
    ifstream os(argv[2]);
    if (!os.is_open()) {
      cout << "Failed to open file!" << endl;
      return 1;
    }
    stringstream buffer;
    buffer << os.rdbuf();
    os.close();
    input = buffer.str();
    isFileInput = true;
  } else if (string(argv[1]) == "-s") {
    // String input
    input = argv[2];
  } else {
    printUsage();
    return 1;
  }

  int line = 1;
  int col = 1;
  cout << (parse(input, line, col) ? "Formatted Correctly"
                                   : "Format INCORRECT!")
       << endl;
  return 0;
}

bool parse(const string &str, int &line, int &col) {
  stack<string> tagStack;
  string tag;
  int n = str.length();
  int i = 0;

  while (i < n) {
    if (str[i] == '\n') {
      line++;
      col = 1;
      i++;
      continue;
    }

    tag = "";
    if (str[i] == '<') {
      int tagStartCol = col; 

      while (i < n && str[i] != '>') {
        tag += str[i++];
        col++;
      }

      if (i < n) {
        tag += str[i++];
        col++;
      }

      if (tag[1] != '/') // Check if it's an opening tag
        tagStack.push(tag);
      else { // It's a closing tag
        if (tagStack.empty()) {
          cout << "Error: Unmatched closing tag:" << line << ':' << tagStartCol << endl;
          return false;
        }

        string openTag = tagStack.top();
        if (generateEndingTag(openTag) != tag) {
          cout << "Error: Tag mismatch:" << line << ':' << tagStartCol << endl;
          return false;
        }
        tagStack.pop();
      }
    } else {
      col++;
      i++;
    }
  }

  if (!tagStack.empty()) {
    cout << "Error: Unmatched opening tag:" << line << ':' << col << endl;
    return false;
  }

  return true;
}

string generateEndingTag(const string &str) {
  string result = "</";
  for (size_t i = 1; i < str.length() && str[i] != ' ' && str[i] != '>'; ++i) {
    result += str[i];
  }
  result += '>';
  return result;
}

bool checkTags(stack<string> s1, stack<string> s2) {
  stack<string> s3;
  string openingTag, closingTag;
  bool matched;

  while (!s1.empty()) {
    openingTag = s1.top();
    s1.pop();
    matched = false;

    while (!s2.empty()) {
      closingTag = s2.top();
      s2.pop();

      if (closingTag == generateEndingTag(openingTag)) {
        matched = true;
        break;
      }
      s3.push(closingTag);
    }

    while (!s3.empty()) {
      s2.push(s3.top());
      s3.pop();
    }

    if (!matched) {
      return false;
    }
  }

  return s2.empty();
}
