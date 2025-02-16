#include <iostream>
#include <fstream>
using namespace std;
int main() {
  ifstream file("cat-1.cpp");
  string word;
  while (!file.eof()) {
    file >> word;
    cout << word;
  }
  file.close();   // optional
  return 0;
}