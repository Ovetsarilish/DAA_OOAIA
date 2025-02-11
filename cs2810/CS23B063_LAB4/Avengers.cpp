#include <bits/stdc++.h>

using namespace std;

/*Class for Quantum Nanotech Suit*/
class QNS{
    public :
        /*Constructors, Copy Constructors*/
        QNS();
        QNS(int powerLevel, int durability, int energyStorage, int heatLevel);
        QNS(const QNS& qns);

        /*Operator Overloading*/
        void operator +(const QNS& otherSuit); //Suit upgrade taking attributes from otherSuit
        void operator -(int X);          //Simulate the damage
        void operator *(int X);          //Activate Power Boost Mode
        void operator /(int X);          //Activate the cooling system, reduce heatLevels

        /*Comparision Overloading*/
        bool operator ==(const QNS& otherSuit);//Compare two suits
        bool operator <(const QNS& otherSuit); //Compare suit effectieveness in battle

        void boostPower(int factor);     //Add power by X, but also increase heatLevels
        void boostPower(const QNS& otherSuit); //Transfer energy from another suit to boost durability

        /*Getters and Setters*/
        int getPowerLevel() const;
        void setPowerLevel(int powerLevel);

        int getDurability() const;
        void setDurability(int durability);

        int getEnergyStorage() const;
        void setEnergyStorage(int energyStorage);

        int getHeatLevel() const;
        void setHeatLevel(int heatLevel);

        bool getIsDestroyed();
        void setIsDestroyed(bool isDestroyed);

        bool getIsShutdown();
        void setIsShutdown(bool isShutdown);

    private :   
        /*Default Attributes*/
        int powerLevel;
        int durability;
        int energyStorage;
        int heatLevel;

        /*Custom attribute*/
        bool isShutdown;
        bool isDestroyed;
};

/*Class for heroes and enemies*/
class Avenger{
    public :
        /*Parameterized constructor*/
        Avenger();
        Avenger(string avName, QNS avSuit, int strength);

        /*Methods for each Avenger*/
        void attack(Avenger& enemy);      //Attacking the enemy
        void upgradeSuit(QNS& otherSuit); //Upgrade if any extra suit is left
        void repair(int x);               //Restore durability by cooling down suit by a factor of x   
        void printStatus();               //Print the P, D, E, H attributes of suit   

        /*getters and setters*/
        string getName();
        void setName(string name);

        QNS& getSuit();
        void setSuit(QNS& suit);

        int getAttackStrength();
        void setAttackStrength(int attackStrength);

    private : 
        /*Default Attributes*/
        string name;
        QNS suit;
        int attackStrength;
};

class Battle{
    public : 
        Battle();
        void startBattle();    //Start simulating the battle 
        void printBattleLog(); //Show batttle history
        int Result();          //Sum power and durability of heroes and enemies currently in ballte, return 0 OR 1 based on comparison

    private : 
        /*Default Attributes*/
        vector<Avenger> heroes;
        vector<Avenger> enemies;
        vector<string> battleLog;

};

/*Implementation of QNS class*/
QNS::QNS(){
    this->powerLevel = 1000;
    this->durability = 500;
    this->energyStorage = 300;
    this->heatLevel = 0;

    this->setPowerLevel(this->powerLevel);
    this->setDurability(this->durability);
    this->setEnergyStorage(this->energyStorage);
    this->setHeatLevel(this->heatLevel);
}

QNS::QNS(int powerLevel, int durability, int energyStorage, int heatLevel){
    this->powerLevel = powerLevel;
    this->durability = durability;
    this->energyStorage = energyStorage;
    this->heatLevel = heatLevel;

    this->setPowerLevel(this->powerLevel);
    this->setDurability(this->durability);
    this->setEnergyStorage(this->energyStorage);
    this->setHeatLevel(this->heatLevel);
}

QNS::QNS(const QNS& otherSuit){
    this->powerLevel = otherSuit.getPowerLevel();
    this->durability = otherSuit.getDurability();
    this->energyStorage = otherSuit.getEnergyStorage();
    this->heatLevel = otherSuit.getHeatLevel();

    this->setPowerLevel(this->powerLevel);
    this->setDurability(this->durability);
    this->setEnergyStorage(this->energyStorage);
    this->setHeatLevel(this->heatLevel);
}

int QNS::getPowerLevel() const{
    return this->powerLevel;
}

void QNS::setPowerLevel(int powerLevel){
    if(powerLevel > 5000){
        this->powerLevel = 5000;
    }else{
        this->powerLevel = powerLevel;
    }
}

bool QNS::getIsDestroyed(){
    return this->isDestroyed;
}

void QNS::setIsDestroyed(bool isDestroyed){
    this->isDestroyed = isDestroyed;
}

bool QNS::getIsShutdown(){
    return this->isShutdown;
}

void QNS::setIsShutdown(bool isShutdown){
    this->isShutdown = isShutdown;
}

int QNS::getDurability() const{
    return this->durability;
}

void QNS::setDurability(int durability){
    if(durability <= 0){
        this->durability = durability;
        this->setIsDestroyed(true);
    }else{
        this->durability = durability;
        this->setIsDestroyed(false);
    }
}

int QNS::getEnergyStorage() const{
    return this->energyStorage;
}

void QNS::setEnergyStorage(int energyStorage){
    this->energyStorage = energyStorage;
}

int QNS::getHeatLevel() const{
    return this->heatLevel;
}

void QNS::setHeatLevel(int heatLevel){
    if(heatLevel <= 0){
        this->heatLevel = 0;
    }else{
        this->heatLevel = heatLevel;
        if(this->heatLevel > 500){
            this->setIsShutdown(true);
        }else{
            this->setIsShutdown(false);
        }
    }
}

void QNS::operator +(const QNS& otherSuit){
    this->setPowerLevel(this->powerLevel + otherSuit.getEnergyStorage());
    this->setDurability(this->durability + otherSuit.getDurability());
    this->setEnergyStorage(this->energyStorage + otherSuit.getPowerLevel());
    this->setHeatLevel(this->heatLevel);
}

void QNS::operator -(int X){
    this->setPowerLevel(this->powerLevel);
    this->setDurability(this->durability - X);
    this->setEnergyStorage(this->energyStorage + X);
    this->setHeatLevel(this->heatLevel + X);
}

void QNS::operator *(int X){
    int oldPower = this->getPowerLevel();
    int newPower = (oldPower + (oldPower *X) / 100);
    this->setPowerLevel(newPower);

    this->setDurability(this->getDurability());

    int newEnergyStorage = this->getEnergyStorage() + (5 * X);
    this->setEnergyStorage(newEnergyStorage);

    this->setHeatLevel(this->getHeatLevel() + X);
}

void QNS::operator /(int X){
    this->setPowerLevel(this->getPowerLevel());
    this->setDurability(this->getDurability() + X);
    this->setEnergyStorage(this->getEnergyStorage());
    this->setHeatLevel(this->getHeatLevel() - X);
}

void QNS::boostPower(int factor){
    (*this) * factor;
    return;
}

bool QNS::operator ==(const QNS& otherSuit){
    return (this->getPowerLevel() == otherSuit.getPowerLevel() &&
            this->getDurability() == otherSuit.getDurability()); 
}

bool QNS::operator <(const QNS& otherSuit){
    int sumOfSuit1 = this->getPowerLevel() + this->getDurability();
    int sumOfSuit2 = otherSuit.getPowerLevel() + otherSuit.getDurability();

    return sumOfSuit1 < sumOfSuit2;
}

void QNS::boostPower(const QNS& otherSuit){
    (*this) + otherSuit;
    return;
}

/*Implementation of Avenger class*/
Avenger::Avenger(){

}

Avenger::Avenger(string avName, QNS avSuit, int strength){
    this->name = avName;
    this->suit = avSuit;
    this->attackStrength = strength;
}

void Avenger::attack(Avenger& enemy){
    enemy.getSuit() - this->getAttackStrength();
}

void Avenger::upgradeSuit(QNS& otherSuit){
    this->getSuit() + otherSuit;
}

void Avenger::repair(int x){
    this->getSuit() / x;
}

void Avenger::printStatus(){
    QNS& ownSuit = this->getSuit();
    cout << this->getName() << " " << ownSuit.getPowerLevel() << " " << ownSuit.getDurability() << " " << ownSuit.getEnergyStorage() << " " << ownSuit.getHeatLevel() << "\n"; 
}

string Avenger::getName(){
    return this->name;
}

void Avenger::setName(string name){
    this->name = name;
}

QNS& Avenger::getSuit(){
    return this->suit;
}

void Avenger::setSuit(QNS& suit){
    this->suit = suit;
}

int Avenger::getAttackStrength(){
    return this->attackStrength;
}

void Avenger::setAttackStrength(int attackStrength){
    this->attackStrength = attackStrength;
}

/*Implementation of Battle class*/
Battle::Battle(){

}

void Battle::startBattle(){
    int k, n, m;
    cin >> k >> n >> m; 
    vector<QNS> qnsSuits;
    int suitPtr = 0;
    for(int i = 0; i < k; i++){
        int p, d, e, h;
        cin >> p >> d >> e >> h;
        QNS suit(p, d, e, h);
        qnsSuits.push_back(suit);
    }

    for(int i = 0; i < n; i++){
        string avName; int strength;
        cin >> avName >> strength;
        if(suitPtr < (int)qnsSuits.size()){
            Avenger a(avName, qnsSuits[suitPtr], strength);
            this->heroes.push_back(a);
            suitPtr++;
        }else{
            cout << avName << " is out of fight" << "\n";
        }
    }

    for(int i = 0; i < m; i++){
        string avName; int strength;
        cin >> avName >> strength;
        if(suitPtr < (int)qnsSuits.size()){
            Avenger a(avName, qnsSuits[suitPtr], strength);
            this->enemies.push_back(a);
            suitPtr++;
        }else{
            cout << avName << " is out of fight" << "\n";
        }
    }


    string battleBegin;
    cin >> battleBegin;
    
    string cmd;
    cin >> cmd;
    while(cmd != "End"){
        if(cmd == "Attack"){
            string av1, av2;
            cin >> av1 >> av2;
            pair<string, int> av1Info; pair<string, int> av2Info;
            for(int i = 0; i < (int)this->heroes.size(); i++){
                if(this->heroes[i].getName() == av1){
                    av1Info = {"hero", i};
                }
                if(this->heroes[i].getName() == av2){
                    av2Info = {"hero", i};
                }
            }

            for(int i = 0; i < (int)this->enemies.size(); i++){
                if(this->enemies[i].getName() == av1){
                    av1Info = {"enemy", i};
                }
                if(this->enemies[i].getName() == av2){
                    av2Info = {"enemy", i};
                }
            }
            Avenger& av1Avenger = (av1Info.first == "hero" ? this->heroes[av1Info.second] : this->enemies[av1Info.second]);
            Avenger& av2Avenger = (av2Info.first == "hero" ? this->heroes[av2Info.second] : this->enemies[av2Info.second]);

            if(!av1Avenger.getSuit().getIsDestroyed() 
                && !av1Avenger.getSuit().getIsShutdown()
                && !av2Avenger.getSuit().getIsDestroyed()){
                av1Avenger.attack(av2Avenger);
                string log = av1 + " attacks " + av2;
                this->battleLog.push_back(log);

                if(av2Avenger.getSuit().getIsDestroyed()){
                    log = av2 + " suit destroyed";
                    this->battleLog.push_back(log);
                }

                if(av2Avenger.getSuit().getIsShutdown() && !av2Avenger.getSuit().getIsDestroyed()){
                    log = av2 + " suit overheated";
                    this->battleLog.push_back(log);
                }
            }
        }else if(cmd == "Repair"){
            string av1; int x;
            cin >> av1 >> x;

            pair<string, int> av1Info; 
            for(int i = 0; i < (int)this->heroes.size(); i++){
                if(this->heroes[i].getName() == av1){
                    av1Info = {"hero", i};
                }
            }

            for(int i = 0; i < (int)this->enemies.size(); i++){
                if(this->enemies[i].getName() == av1){
                    av1Info = {"enemy", i};
                }
            }
            
            Avenger& av1Avenger = (av1Info.first == "hero" ? this->heroes[av1Info.second] : this->enemies[av1Info.second]);
            if(!av1Avenger.getSuit().getIsDestroyed()){
                av1Avenger.repair(x);
                string log = av1 + " repaired";
                this->battleLog.push_back(log);
            }
        }else if(cmd == "BoostPowerByFactor"){
            string av1; int y;
            cin >> av1 >> y;

            pair<string, int> av1Info; 
            for(int i = 0; i < (int)this->heroes.size(); i++){
                if(this->heroes[i].getName() == av1){
                    av1Info = {"hero", i};
                }
            }

            for(int i = 0; i < (int)this->enemies.size(); i++){
                if(this->enemies[i].getName() == av1){
                    av1Info = {"enemy", i};
                }
            }

            Avenger& av1Avenger = (av1Info.first == "hero" ? this->heroes[av1Info.second] : this->enemies[av1Info.second]);
            if(!av1Avenger.getSuit().getIsDestroyed()){
                av1Avenger.getSuit().boostPower(y);
                string log = av1 + " boosted";
                this->battleLog.push_back(log);

                if(av1Avenger.getSuit().getIsShutdown()){
                    log = av1 + " suit overheated";
                    this->battleLog.push_back(log);
                }
            }
        }else if(cmd == "BoostPower"){
            string av1; int p, d, e, h;
            cin >> av1, p, d, e, h;
            QNS newSuit(p, d, e, h);

            pair<string, int> av1Info; 
            for(int i = 0; i < (int)this->heroes.size(); i++){
                if(this->heroes[i].getName() == av1){
                    av1Info = {"hero", i};
                }
            }

            for(int i = 0; i < (int)this->enemies.size(); i++){
                if(this->enemies[i].getName() == av1){
                    av1Info = {"enemy", i};
                }
            }

            Avenger& av1Avenger = (av1Info.first == "hero" ? this->heroes[av1Info.second] : this->enemies[av1Info.second]);
            if(!av1Avenger.getSuit().getIsDestroyed()){
                av1Avenger.upgradeSuit(newSuit);

                string log = av1 + " upgraded";
                this->battleLog.push_back(log);
            }
        }else if(cmd == "AvengerStatus"){
            string av1;
            cin >> av1;

            pair<string, int> av1Info; 
            for(int i = 0; i < (int)this->heroes.size(); i++){
                if(this->heroes[i].getName() == av1){
                    av1Info = {"hero", i};
                }
            }

            for(int i = 0; i < (int)this->enemies.size(); i++){
                if(this->enemies[i].getName() == av1){
                    av1Info = {"enemy", i};
                }
            }

            Avenger& av1Avenger = (av1Info.first == "hero" ? this->heroes[av1Info.second] : this->enemies[av1Info.second]);
            av1Avenger.printStatus();
        }else if(cmd == "Upgrade"){
            string av1;
            cin >> av1;

            pair<string, int> av1Info; 
            for(int i = 0; i < (int)this->heroes.size(); i++){
                if(this->heroes[i].getName() == av1){
                    av1Info = {"hero", i};
                }
            }

            for(int i = 0; i < (int)this->enemies.size(); i++){
                if(this->enemies[i].getName() == av1){
                    av1Info = {"enemy", i};
                }
            }

            Avenger& av1Avenger = (av1Info.first == "hero" ? this->heroes[av1Info.second] : this->enemies[av1Info.second]);
            if(!av1Avenger.getSuit().getIsDestroyed()){
                if(suitPtr < (int)qnsSuits.size()){
                    QNS upgradedSuit = qnsSuits[suitPtr];
                    av1Avenger.upgradeSuit(upgradedSuit);
                    suitPtr++;

                    string log = av1 + " upgraded";
                    this->battleLog.push_back(log);
                }else{
                    string log = av1 + " upgrade Fail";
                    this->battleLog.push_back(log);
                }
            }
        }else if(cmd == "PrintBattleLog"){
            this->printBattleLog();
        }else if(cmd == "BattleStatus"){
            int result = this->Result();
            if(result == 1){
                cout << "heroes are winning" << "\n";
            }else if(result == -1){
                cout << "enemies are winning" << "\n";
            }else{
                cout << "tie" << "\n";
            }
        }else if(cmd == "End"){
            break;
        }else{
            assert(false);
        }
        cin >> cmd;
    } 
}

void Battle::printBattleLog(){
    for(int i = 0; i < (int)this->battleLog.size(); i++){
        cout << this->battleLog[i] << "\n";
    }
}

int Battle::Result(){
    int heroSum = 0; int enemySum = 0;
    for(int i = 0; i < (int)this->heroes.size(); i++){
        QNS& suit = this->heroes[i].getSuit();
        if(!suit.getIsDestroyed()){
            heroSum += suit.getPowerLevel() + suit.getDurability();
        }
    }

    for(int i = 0; i < (int)this->enemies.size(); i++){
        QNS& suit = this->enemies[i].getSuit();
        if(!suit.getIsDestroyed()){
            enemySum += suit.getPowerLevel() + suit.getDurability();
        }
    }

    if(heroSum > enemySum){
        return 1;
    }else if(heroSum < enemySum){
        return -1;
    }else{
        return 0;
    }
}

int main(){
    Battle battle;
    battle.startBattle();
}