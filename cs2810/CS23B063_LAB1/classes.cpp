#include <bits/stdc++.h>

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
        vector<BTech*> DPPProjectees;
        vector<DualDegree*> taSupervisee;

        Faculty(){
            name = "John Doe";
            isPermanent = true;
        }

        Faculty(string name_, bool isPermanent_){
            name = name_; 
            isPermanent = isPermanent_;
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
class BTech{
    public :
        string name; 
        string rollNumber;
        string hostel;
        int cgpa;
        Faculty* facad;
        Faculty* BTPGuide;

        BTech(){

        }

        BTech(string name_, string rollNumber_, string hostel_, Faculty* facad_, int cgpa_){
            name = name_;
            rollNumber = rollNumber_;
            hostel = hostel_;
            facad = facad_;
            cgpa = cgpa_;
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

class DualDegree{
    public :
        string name; 
        string rollNumber;
        string hostel;
        int cgpa;
        
        Faculty* DDPGuide;
        Faculty* taSupervisor;
        Faculty* facad;
        
        DualDegree(){

        }

        DualDegree(string name_, string rollno_, string hostel_, Faculty* facad_, int cgpa_){
            name = name_;
            rollNumber = rollno_;
            hostel = hostel_;
            facad = facad_;
            cgpa = cgpa_;
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
            this->DDPGuide = faculty;
        }

        Faculty* getTASupervisor(){
            return taSupervisor;
        }

        void setTASupervisor(Faculty* faculty){
            this->taSupervisor = faculty;
        }

        int getCGPA(){
            return cgpa;
        }
};
