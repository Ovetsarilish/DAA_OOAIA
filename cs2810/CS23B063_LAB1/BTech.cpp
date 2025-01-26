#pragma once

#include <iostream>
#include <string.h>

#include "Faculty.cpp"

using namespace std;

class BTech{
    public :
        string name; 
        string rollNumber;
        string hostel;
        int cgpa;
        Faculty* facad;
        Faculty* BTPGuide;

        BTech(string name, string rollno, string hostel, Faculty* facad, float cgpa){
            name = name;
            rollNumber = rollno;
            hostel = hostel;
            facad = facad;
            cgpa = cgpa;
            BTPGuide = new Faculty("John Doe", true);
        }

        string getHostel(){
            return hostel;
        }

        Faculty* getFacad(){
            return facad;
        }

        void changeHostel(string changedHostel){
            hostel = changedHostel;
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