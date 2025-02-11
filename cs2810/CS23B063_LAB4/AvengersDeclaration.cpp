#include <bits/stdc++.h>

using namespace std;

/*Class for Quantum Nanotech Suit*/
class QNS{
    public :
        /*Constructors, Copy Constructors*/
        QNS();
        QNS(int powerLevel, int durability, int energyStorage, int heatLevel);
        QNS(QNS& qns);

        /*Operator Overloading*/
        void operator +(QNS& otherSuit); //Suit upgrade taking attributes from otherSuit
        void operator -(int X);          //Simulate the damage
        void operator *(int X);          //Activate Power Boost Mode
        void operator /(int X);          //Activate the cooling system, reduce heatLevels

        /*Comparision Overloading*/
        bool operator ==(QNS& otherSuit);//Compare two suits
        bool operator <(QNS& otherSuit); //Compare suit effectieveness in battle

        void boostPower(int factor);     //Add power by X, but also increase heatLevels
        void boostPower(QNS& otherSuit); //Transfer energy from another suit to boost durability

        /*Getters and Setters*/
        int getPowerLevel();
        void setPowerLevel(int powerLevel);

        int getDurability();
        void setDurability(int durability);

        int getEnergyStorage();
        void setEnergyStorage(int energyStorage);

        int getHeatLevel();
        void setHeatLevel(int heatLevel);

    private :   
        /*Default Attributes*/
        int powerLevel;
        int durability;
        int energyStorage;
        int heatLevel;
};

/*Class for heroes and enemies*/
class Avenger{
    public :
        /*Parameterized constructor*/
        Avenger(string avName, QNS avSuit, int strength);

        /*Methods for each Avenger*/
        void attack(Avenger& enemy); //Attacking the enemy
        void upgradeSuit();          //Upgrade if any extra suit is left
        void repair(int x);          //Restore durability by cooling down suit by a factor of x   
        void printStatus();          //Print the P, D, E, H attributes of suit   

    private : 
        /*Default Attributes*/
        string name;
        QNS suit;
        int attackStrength;
};

class Battle{
    public : 
        void startBattle();    //Start simulating the battle 
        void printBattleLog(); //Show batttle history
        int Result();          //Sum power and durability of heroes and enemies currently in ballte, return 0 OR 1 based on comparison

    private : 
        /*Default Attributes*/
        vector<Avenger> heroes;
        vector<Avenger> enemies;
        vector<string> battleLog;

};

int main(){
    return 0;
}