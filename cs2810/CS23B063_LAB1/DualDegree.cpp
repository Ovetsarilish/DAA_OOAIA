#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include "Faculty.cpp"

using namespace std;

class Faculty;

class DualDegree{
    public :
        string name; 
        string rollNumber;
        string hostel;
        int cgpa;
        
        Faculty* DDPGuide;
        Faculty* taSupervisor;
        Faculty* facad;

        DualDegree(string name, string rollno, string hostel, float cgpa){
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
            hostel = changedHostel;
        }

        Faculty* getDDPGuide(){
            return DDPGuide;
        }

        void setDDPGuide(Faculty* faculty){
            DDPGuide = faculty;
        }

        Faculty* getTASupervisor(){
            return taSupervisor;
        }

        void setTASupervisor(Faculty* faculty){
            taSupervisor = faculty;
        }

        int getCGPA(){
            return cgpa;
        }
};