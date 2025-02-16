#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
  /*Writing to file*/
  char ch = 'x';
  int j = 77;
  double d = 6.02;
  string str1 = "Kafka";
  string str2 = "Proust";
//for file I/O
  ofstream outfile("fdata.txt"); //create ofstream object
  outfile << ch
        << j
        << ' '
        << d
        << str1
        << ' '
        << str2;
  cout << "File written\n";

  /*Reading from file*/
  // char ch; int j;
  // double d;
  // string str1; string str2;
  // ifstream infile("fdata.txt"); //create ifstream object
  // //extract (read) data from it
  // infile >> ch >> j >> d >> str1 >> str2;
  // cout << ch << endl //display the data
  // << j << endl
  // << d << endl
  // << str1 << endl
  // << str2 << endl;

  
  return 0;
}