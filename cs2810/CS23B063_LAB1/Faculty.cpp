#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include "BTech.cpp"
#include "DualDegree.cpp"

using namespace std;

class Faculty{
    public :
        string name;
        bool isPermanent;
        int numberOfBTPGuides;
        int numberOfDDPGuides;
        int numberOfSupervisees;
        vector<BTech*> BTPProjectees;
        vector<BTech*> DPPProjectees;
        vector<DualDegree*> taSupervisee;

        Faculty(string name, bool isPermanent){
            name = name; 
            isPermanent = isPermanent;
            numberOfBTPGuides = 0;
            numberOfDDPGuides = 0;
            numberOfSupervisees = 0;
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

};