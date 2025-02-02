#pragma once

#include <random>
#include <bits/stdc++.h>

// #include "classes.cpp"
#include "Faculty.cpp"
#include "DualDegree.cpp"
#include "BTech.cpp"

using namespace std;

bool compareRollDD(DualDegree* const a, DualDegree* const b){
    return a->rollNumber < b->rollNumber;
}

bool compareHostelDD(DualDegree* const a, DualDegree* const b){
    return a->hostel.compare(b->hostel);
}

bool compareFaculties(Faculty* const a, Faculty* const b){
    return a->name.compare(b->name);
}

bool compareGuideDD(DualDegree* const a, DualDegree* const b){
    return compareFaculties(a->getDDPGuide(), b->getDDPGuide());
}

bool compareRollBT(BTech* const a, BTech* const b){
    return a->rollNumber < b->rollNumber;
}

bool compareCGBT(BTech* const a, BTech* const b){
    return a->getCGPA() > b->getCGPA();
}

bool compareHostelBT(BTech* const a, BTech* const b){
    return a->hostel.compare(b->hostel);
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
                bTechStudents.push_back(new BTech(getRandomString(), getRandomString(), hostels[rand() % 5], rand() % (10 - 1) + 1));
                faculties[rand() % (int)faculties.size()]->addMentee(bTechStudents[i]);
            }
        }

        void generateRandomDD(int n){
            for(int i = 0; i < n; i++){
                ddStudents.push_back(new DualDegree(getRandomString(), getRandomString(), hostels[rand() % 5], rand() % (10 - 1) + 1));
                faculties[rand() % (int)faculties.size()]->addMentee(ddStudents[i]);
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
            sort(bTechStudents.begin(), bTechStudents.end(), compareHostelBT);
            int maxBTP = 2;
            int studentPtr = 0; int facultyPtr = 0;
            while(studentPtr < (int)bTechStudents.size() && facultyPtr < (int)faculties.size()){
                if(faculties[facultyPtr]->numBTP() < maxBTP){
                    // bTechStudents[studentPtr]->BTPGuide = faculties[facultyPtr];
                    faculties[facultyPtr]->addBTPProjectees(bTechStudents[studentPtr]);
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
                    // ddStudents[studentPtr]->DDPGuide = faculties[facultyPtr];
                    faculties[facultyPtr]->addDDPProjectees(ddStudents[studentPtr]);
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
                    // ddStudents[studentPtr]->taSupervisor = faculties[facultyPtr];
                    faculties[facultyPtr]->addTASupervisees(ddStudents[studentPtr]);
                    faculties[facultyPtr]->numberOfSupervisees++;
                    studentPtr++;
                }else{
                    facultyPtr++;
                }
            }
        }

        void printFac(){
            sort(faculties.begin(), faculties.end(), compareFaculties);
            for(int i = 0; i < (int)faculties.size(); i++){
                cout << faculties[i]->name << " ";
            }
            cout << "\n";
        }

        void printBT(){
            // sort(bTechStudents.begin(), bTechStudents.end(), compareRollBT);
            // cout << "Sorted by Roll : \n";
            // for(int i = 0; i < (int)bTechStudents.size(); i++){
            //     cout << bTechStudents[i]->name << " " << bTechStudents[i]->rollNumber << " " << bTechStudents[i]->getFacad()->name << "\n";
            // }

            // sort(bTechStudents.begin(), bTechStudents.end(), compareHostelBT);
            // cout << "Sorted by Hostel : \n";
            // for(int i = 0; i < (int)bTechStudents.size(); i++){
            //     cout << bTechStudents[i]->name << " " << bTechStudents[i]->rollNumber << " " << bTechStudents[i]->getFacad()->name << "\n";
            // }
            // cout << "\n";
        }

        void printDD(){
            sort(ddStudents.begin(), ddStudents.end(), compareRollDD);
            // cout << "Sorted by Roll : \n";
            // for(int i = 0; i < (int)ddStudents.size(); i++){
            //     cout << ddStudents[i]->name << " " << ddStudents[i]->rollNumber << " " << ddStudents[i]->getFacad()->name << "\n";
            // }
            cout << ddStudents[0]->getDDPGuide()->name << "\n";

            // cout << "Sorted by Guide name : \n";
            sort(ddStudents.begin(), ddStudents.end(), compareGuideDD);
            // for(int i = 0; i < (int)ddStudents.size(); i++){
            //     cout << ddStudents[i]->name << " " << ddStudents[i]->rollNumber << " " << ddStudents[i]->getFacad()->name << "\n";
            // }

            cout << ddStudents[0]->getDDPGuide()->name << "\n";
            // sort(ddStudents.begin(), ddStudents.end(), compareHostelDD);
            // cout << "Sorted by Hostel : \n";
            // for(int i = 0; i < (int)ddStudents.size(); i++){
            //     cout << ddStudents[i]->name << " " << ddStudents[i]->rollNumber << " " << ddStudents[i]->getFacad()->name << "\n";
            // }
        }
};