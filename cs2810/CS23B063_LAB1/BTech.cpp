#pragma once

#include <iostream>
#include <string.h>

#include "Faculty.cpp"

using namespace std;

class Faculty;

class BTech{
    public :
        string name; 
        string rollNumber;
        string hostel;
        int cgpa;

        Faculty* facad;
        Faculty* BTPGuide;

        BTech(string name, string rollno, string hostel, float cgpa){
            this->name = name;
            this->rollNumber = rollno;
            this->hostel = hostel;
            this->cgpa = cgpa;
        }

        string getHostel(){
            return hostel;
        }

        Faculty* getFacad(){
            return facad;
        }

        void changeHostel(string changedHostel){
            this->hostel = changedHostel;
        }

        Faculty* getBTPGuide(){
            return BTPGuide;
        }

        void setBTPGuide(Faculty* faculty){
            BTPGuide = faculty;
        }

        int getCGPA(){
            return cgpa;
        }

};