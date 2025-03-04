#include <bits/stdc++.h>

using namespace std;

vector<bool> sieve((int)1e6 + 10, true);

class Numbers{
    public :
        Numbers(double x, double y);

        virtual void add(double x, double y);
        virtual void mul(double x, double y);
        virtual void sub(double x, double y);

        double getX();
        double getY();
    private :
        double x;
        double y;
};

class Rational : public Numbers{
    public :
        Rational(double x, double y) : Numbers(x, y){};

        void add(double x, double y);
        void mul(double x, double y);
        void sub(double x, double y);
        void reduce();
};

class Complex : public Numbers{
    public :
        Complex(double x, double y) : Numbers(x, y){};

        void add(double x, double y);
        void mul(double x, double y);
        void sub(double x, double y);
};

class Natural{
    public :    
        Natural(int num);
        void checkPrime();
        long long inversePrime(long long MOD);

    private :
        int num;
};

void Numbers::add(double x, double y){
    
}

void Numbers::sub(double x, double y){
    
}

void Numbers::mul(double x, double y){
    
}

Numbers::Numbers(double x, double y){
    this->x = x;
    this->y = y;
}

double Numbers::getX(){
    return this->x;
}

double Numbers::getY(){
    return this->y;
}

void Rational::add(double x, double y){
    double r1 = this->getX() / this->getY();
    double r2 = x / y;

    cout << setiosflags(ios::fixed) << setprecision(3) << r1 + r2 << "\n";
}

void Rational::mul(double x, double y){
    double r1 = this->getX() / this->getY();
    double r2 = x / y;

    cout << setiosflags(ios::fixed) << setprecision(3) << r1 * r2 << "\n";
}

void Rational::sub(double x, double y){
    double r1 = this->getX() / this->getY();
    double r2 = x / y;

    cout << setiosflags(ios::fixed) << setprecision(3) << r1 - r2 << "\n";
}

void Rational::reduce(){
    int numerator = (int)this->getX();
    int denominator = (int)this->getY();

    int gcd = __gcd(numerator, denominator);

    numerator /= gcd;
    denominator /= gcd;

    cout << (numerator < 0 && denominator > 0 || numerator > 0 && denominator < 0 ? "-" : "") << abs(numerator) << " " << abs(denominator) << "\n";
}

void Complex::add(double x, double y){
    double r1 = this->getX(); 
    double i1 = this->getY();

    double r2 = x;
    double i2 = y;

    cout << setiosflags(ios::fixed) << setprecision(3) << (r1 + r2) << " " << (i1 + i2) << "\n";
}

void Complex::mul(double x, double y){
    double r1 = this->getX(); 
    double i1 = this->getY();

    double r2 = x;
    double i2 = y;

    double realMul = r1 * r2;
    double imagMul = i1 * i2;
    double crossMul = r1 * i2 + i1 * r2;

    cout << setiosflags(ios::fixed) << setprecision(3) << (realMul - imagMul) << " " << (crossMul) << "\n";
}

void Complex::sub(double x, double y){
    double r1 = this->getX(); 
    double i1 = this->getY();

    double r2 = x;
    double i2 = y;

    cout << setiosflags(ios::fixed) << setprecision(3) << (r1 - r2) << " " << (i1 - i2) << "\n";
}

void Natural::checkPrime(){
    cout << (sieve[this->num] ? 1 : 0) << "\n";
}

Natural::Natural(int num){
    this->num = num;
}

long long Natural::inversePrime(long long MOD){
    long long m0 = MOD;
    long long y = 0, x = 1;
    long long A = this->num;

    if (MOD == 1)
        return 0;

    while (A > 1) {
        // q is quotient
        long long q = A / MOD;
        long long t = MOD;

        // m is remainder now, process same as
        // Euclid's algo
        MOD = A % MOD, A = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}

void precompute(){
    for (int p = 2; p * p < (int)1e6 + 10; p++) {
        if (sieve[p] == true) {
            
            // Update all multiples of p greater than or
            // equal to the square of it numbers which are
            // multiple of p and are less than p^2 are
            // already been marked.
            for (int i = p * p; i < (int)1e6 + 10; i += p)
                sieve[i] = false;
        }
    }
}

int main(){
    int n; 
    cin >> n;
    precompute();
    while(n--){
        string s, op;
        cin >> s >> op;
        if(s == "complex"){
            double r1, r2, i1, i2;
            cin >> r1 >> i1 >> r2 >> i2;
            Complex c1(r1, i1);
            if(op == "add"){
                c1.add(r2, i2);
            }else if(op == "sub"){
                c1.sub(r2, i2);
            }else if(op == "mult"){
                c1.mul(r2, i2);
            }
        }else if(s == "rational"){
            double r1, r2, r3, r4;
            cin >> r1 >> r2;
            Rational rat(r1, r2);
            if(op == "add"){
                cin >> r3 >> r4;
                rat.add(r3, r4);
            }else if(op == "sub"){
                cin >> r3 >> r4;
                rat.sub(r3, r4);
            }else if(op == "mult"){
                cin >> r3 >> r4;
                rat.mul(r3, r4);
            }else if(op == "reduce"){
                rat.reduce();
            }
        }else if(s == "natural"){
            int n;
            cin >> n;
            Natural nat(n);
            if(op == "isprime"){
                nat.checkPrime();
            }else if(op == "inverse"){
                long long MOD = 1000000007;
                long long res = nat.inversePrime(MOD);
                cout << res << "\n";
            }
        }

    }
}