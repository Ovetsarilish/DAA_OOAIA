#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include "BTech.cpp"
#include "DualDegree.cpp"

using namespace std;
class BTech;
class DualDegree;

class Faculty{
    public :
        string name;
        bool isPermanent;
        int numberOfBTPGuides;
        int numberOfDDPGuides;
        int numberOfSupervisees;
        vector<BTech*> BTPProjectees;
        vector<DualDegree*> DDPProjectees;
        vector<DualDegree*> taSupervisee;

        Faculty(string name, bool isPermanent){
            this->name = name; 
            this->isPermanent = isPermanent;
            this->numberOfBTPGuides = 0;
            this->numberOfDDPGuides = 0;
            this->numberOfSupervisees = 0;
        }

        int numBTP(){
            return numberOfBTPGuides;
        }

        int numDDP(){
            return numberOfDDPGuides;
        }

        int numSupervisees(){
            return numberOfSupervisees;
        }

        void addMentee(BTech* student){
            student->facad = this;
        }

        void addMentee(DualDegree* student){
            student->facad = this;
        }

        void addDDPProjectees(DualDegree* student){
            DDPProjectees.push_back(student);
            student->DDPGuide = this;
        }

        void addBTPProjectees(BTech* student){
            BTPProjectees.push_back(student);
            student->BTPGuide = this;
        }

        void addTASupervisees(DualDegree* student){
            taSupervisee.push_back(student);
            student->taSupervisor = this;
        }

};