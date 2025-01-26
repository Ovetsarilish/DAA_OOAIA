#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include "Faculty.cpp"

using namespace std;

class DualDegree{
    public :
        string name; 
        string rollNumber;
        string hostel;
        int cgpa;
        
        Faculty* DDPGuide;
        Faculty* taSupervisor;
        Faculty* facad;
        

        DualDegree(string name, string rollno, string hostel, Faculty* facad, float cgpa){
            name = name;
            rollNumber = rollno;
            hostel = hostel;
            facad = facad;
            cgpa = cgpa;

            DDPGuide = new Faculty("John Doe", true);
            taSupervisor = new Faculty("John Doe", true);
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