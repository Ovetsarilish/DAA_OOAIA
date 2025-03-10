#include <bits/stdc++.h>
using namespace std;

class Polynomial{
    public:
        Polynomial(int size);// constructor for resizing coeffArray
        void insertTerm(int coef, int exp); // insert the coefficient of x^exp
        Polynomial add(Polynomial & rhs); // add  rhs and the caller object
        Polynomial mul(Polynomial & rhs);// multiply rhs and called object
        void print();// print the object
    private:
        vector<int> coeffArray;
};

Polynomial::Polynomial(int size){
    coeffArray.resize(size + 1);
}

Polynomial Polynomial::add(Polynomial &rhs){
    Polynomial p(max(coeffArray.size() - 1, rhs.coeffArray.size() - 1));
    int j = 0; int k = 0; int i = 0;
    while(j < coeffArray.size() && k < rhs.coeffArray.size()){
        p.coeffArray[i++] = coeffArray[j++] + rhs.coeffArray[k++];
    }
    while(j < coeffArray.size()){
        p.coeffArray[i++] = coeffArray[j++];
    }
    while(k < rhs.coeffArray.size()){
        p.coeffArray[i++] = rhs.coeffArray[k++];
    }
    return p;
}

Polynomial Polynomial::mul(Polynomial &rhs){
    Polynomial p(coeffArray.size() + rhs.coeffArray.size());
    for(int j = 0; j < coeffArray.size(); j++){
        for(int k = 0; k < rhs.coeffArray.size(); k++){
            p.coeffArray[j + k] += (coeffArray[j] * rhs.coeffArray[k]);  
        }
    }
    return p;
}

void Polynomial::insertTerm(int coef, int exp){
    coeffArray[exp] = coef;
    // cout << coef << " " << exp << "\n";
    // cout << coeffArray.size() << "\n";
}

void Polynomial::print(){
    bool ok = false;
    for(int i = coeffArray.size() - 1; i >= 0; i--){
        if(!ok){
            if(coeffArray[i] != 0){
                cout << coeffArray[i] << "*x^" << i;
                ok = true;
            }
        }else{ 
            if(coeffArray[i] != 0){
                cout << " + " << coeffArray[i] << "*x^" << i; 
            }
        }
    }
    cout << "\n";
}

int main(){
    int m, n;
    cin >> n;
    vector<pair<int, int>> p1_;
    vector<pair<int, int>> p2_;
    int maxe1 = 0; int maxe2 = 0;
    for(int i = 0; i < n; i++){
        int coef, exp;
        cin >> coef >> exp;
        maxe1 = max(maxe1, exp);
        p1_.push_back({coef, exp});
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        int coef, exp;
        cin >> coef >> exp;
        maxe2 = max(maxe2, exp);
        p2_.push_back({coef, exp});
    }
    Polynomial p2(maxe2);
    Polynomial p1(maxe1);
    for(int i = 0; i < p1_.size(); i++){
        p1.insertTerm(p1_[i].first, p1_[i].second);
    }
    for(int i = 0; i < p2_.size(); i++){
        p2.insertTerm(p2_[i].first, p2_[i].second);
    }
    // p1.print();
    // p2.print();
    Polynomial a = p1.add(p2);
    Polynomial mu = p1.mul(p2);

    a.print();
    mu.print();
}