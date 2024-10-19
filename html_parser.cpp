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

bool parse(const string &str);
string generateEndingTag(const string &str);
bool checkTags(stack<string> s1, stack<string> s2);

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

    // Process the HTML input and check for formatting correctness
    cout << (parse(input) ? "Formatted Correctly" : "Format INCORRECT!") << endl;

    return 0;
}

bool parse(const string &str) {
    stack<string> tagStack;
    string tag;
    int n = str.length();
    int i = 0;

    while (i < n) {
        tag = "";
        if (str[i] == '<') {
            while (i < n && str[i] != '>')
                tag += str[i++];
            tag += str[i++];

            if (tag[1] != '/')
                tagStack.push(tag);
            else {
                if (tagStack.empty())
                    return false;
                string openTag = tagStack.top();
                if (generateEndingTag(openTag) != tag)
                    return false;
                tagStack.pop();
            }
        } else
            i++;
    }

    return tagStack.empty();
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
