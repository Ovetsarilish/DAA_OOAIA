#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char * argv[]) {
  ifstream ifile(argv[1]);
  ofstream ofile(argv[2]);
  string line;
  while (!ifile.eof()) {
    getline(ifile, line);
    ofile << line << endl;
  }
  ifile.close();
  ofile.close();
  return 0;
}