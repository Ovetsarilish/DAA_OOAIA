#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char * argv[]) {
  if (argc != 3)
  {
    cerr << "Usage: " << argv[0] << " <inputfile> <outputfile>" << endl;
    exit(1);
  }
  ifstream ifile(argv[1]);
  if (ifile.fail())
  {
    cerr << "File " << argv[1] << " could not be opened." << endl;
    exit(1);
  }
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