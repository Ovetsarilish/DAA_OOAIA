#pragma once

#include <random>
#include <bits/stdc++.h>

#include "classes.cpp"

using namespace std;

bool compareRollDD(DualDegree* a, DualDegree* b){
    return (*a).rollNumber < (*b).rollNumber;
}

bool compareHostelDD(DualDegree* a, DualDegree* b){
    return a->hostel < b->hostel;
}

bool compareGuideDD(DualDegree* a, DualDegree* b){
    return (a->getDDPGuide()->name) < (b->getDDPGuide()->name);
}

bool compareRollBT(BTech* a, BTech* b){
    return a->rollNumber < b->rollNumber;
}

bool compareCGBT(BTech* a, BTech* b){
    return a->getCGPA() > b->getCGPA();
}

bool compareHostelBT(BTech* a, BTech* b){
    return a->hostel < b->hostel;
}


class IITM{
    public :
        vector<string> hostels = {"Mandak", "Cauvery", "Alak", "Jamuna", "Sharav"};
        vector<BTech*> bTechStudents;
        vector<DualDegree*> ddStudents;
        vector<Faculty*> faculties;
        
        string alphaNumeric = "abcdefghijklmnopqrstuvwxyz0123456789";

        IITM(){

        }

        void generateRandomBTech(int n){
            for(int i = 0; i < n; i++){
                bTechStudents.push_back(new BTech(getRandomString(), getRandomString(), hostels[rand() % 5], faculties[rand() % (int)faculties.size()], rand() % (10 - 1) + 1));
            }
        }

        void generateRandomDD(int n){
            for(int i = 0; i < n; i++){
                ddStudents.push_back(new DualDegree(getRandomString(), getRandomString(), hostels[rand() % 5], faculties[rand() % (int)faculties.size()], rand() % (10 - 1) + 1));
            }
        }

        void generateRandomFaculty(int n){
            for(int i = 0; i < n; i++){
                faculties.push_back(new Faculty(getRandomString(), rand() % 2));
            }
        }

        string getRandomString(){
            string ret = "";
            for(int i = 0; i < 7; i++){
                ret += alphaNumeric[rand() % 36];
            }
            return ret;
        }

        void assignBTP(){
            sort(bTechStudents.begin(), bTechStudents.end(), compareCGBT);
            int maxBTP = 2;
            int studentPtr = 0; int facultyPtr = 0;
            while(studentPtr < (int)bTechStudents.size() && facultyPtr < (int)faculties.size()){
                if(faculties[facultyPtr]->numBTP() < maxBTP){
                    bTechStudents[studentPtr]->BTPGuide = faculties[facultyPtr];
                    faculties[facultyPtr]->numberOfBTPGuides++;
                    studentPtr++;
                }else{
                    facultyPtr++;
                }
            }
        }

        void assignDDP(){
            sort(ddStudents.begin(), ddStudents.end(), compareHostelDD);
            int maxDDP = 2;
            int studentPtr = 0; int facultyPtr = 0;
            while(studentPtr < (int)ddStudents.size() && facultyPtr < (int)faculties.size()){
                if(faculties[facultyPtr]->numDDP() < maxDDP){
                    ddStudents[studentPtr]->DDPGuide = faculties[facultyPtr];
                    cout << ddStudents[studentPtr]->DDPGuide->name << "\n";
                    faculties[facultyPtr]->numberOfDDPGuides++;
                    studentPtr++;
                }else{
                    facultyPtr++;
                }
            }
        }

        void assignTASupervisees(){
            int maxTASupervisees = 5;
            int studentPtr = 0; int facultyPtr = 0;
            while(studentPtr < (int)ddStudents.size() && facultyPtr < facultyPtr < (int)faculties.size()){
                if(faculties[facultyPtr]->numBTP() < maxTASupervisees){
                    ddStudents[studentPtr]->taSupervisor = faculties[facultyPtr];
                    faculties[facultyPtr]->numberOfSupervisees++;
                    studentPtr++;
                }else{
                    facultyPtr++;
                }
            }
        }

        void printBT(){
            sort(bTechStudents.begin(), bTechStudents.end(), compareRollBT);
            cout << "Sorted by Roll : \n";
            for(int i = 0; i < (int)bTechStudents.size(); i++){
                cout << bTechStudents[i]->name << " " << bTechStudents[i]->rollNumber << " " << bTechStudents[i]->getFacad()->name << "\n";
            }

            sort(bTechStudents.begin(), bTechStudents.end(), compareHostelBT);
            cout << "Sorted by Hostel : \n";
            for(int i = 0; i < (int)bTechStudents.size(); i++){
                cout << bTechStudents[i]->name << " " << bTechStudents[i]->rollNumber << " " << bTechStudents[i]->getFacad()->name << "\n";
            }
        }

        void printDD(){
            sort(ddStudents.begin(), ddStudents.end(), compareRollDD);
            cout << "Sorted by Roll : \n";
            for(int i = 0; i < (int)ddStudents.size(); i++){
                cout << ddStudents[i]->name << " " << ddStudents[i]->rollNumber << ddStudents[i]->getFacad()->name << "\n";
            }

            sort(ddStudents.begin(), ddStudents.end(), compareHostelDD);
            cout << "Sorted by Hostel : \n";
            for(int i = 0; i < (int)ddStudents.size(); i++){
                cout << ddStudents[i]->name << " " << ddStudents[i]->rollNumber << " " << ddStudents[i]->getFacad()->name << "\n";
            }
        }
};