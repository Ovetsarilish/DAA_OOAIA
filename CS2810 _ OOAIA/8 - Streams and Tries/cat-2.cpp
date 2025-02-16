#include <iostream>
#include <fstream>
using namespace std;
int main() {
  ifstream file("cat-2.cpp");
  string line;
  while (!file.eof()) {
    getline(file, line);
    cout << line << endl;
  }
  file.close();   // optional
  return 0;
}