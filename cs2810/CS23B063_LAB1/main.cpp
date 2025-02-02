#include "IITM.cpp"

int main(){
    IITM admin;
    admin.generateRandomFaculty(6);
    admin.generateRandomBTech(20);
    admin.generateRandomDD(20);

    admin.assignBTP();
    admin.assignDDP();

    cout << "BTech list : \n";
    admin.printBT();
    // cout << "Dual Degree list : \n";
    // admin.printDD();

    cout << "FACS : \n";
    admin.printFac();
}