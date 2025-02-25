#include <bits/stdc++.h>
#define MOD (int)(1e9 + 7)
using namespace std;

vector<bool> sieve(1e6 + 10, false);
vector<int> primes;
vector<int> squares;

/*We can use stucts as well*/
class CurrencySorter{
    public :
        void operator() (vector<int> &v);                   //overloading the () operator
        void quickSort(vector<int> &v, int low, int high);  //partition part of the quicksort function
        int partition(vector<int> &v, int low, int high);   //quicksort function which is called upon recursively
};

class FibonacciGenerator{
    public :
        long long operator() (long long i);     //overloading the () operator for functor use

        /*utility function to calculate fibonacci numbers using matrix multiplication*/
        void multiply(vector<long long> &A, vector<long long> &B);

        /*function to perform matrix multiplication*/
        vector<long long> power(vector<long long> M, long long exp);

        long long fibCalc(long long n);
};

class PrimeCalculator{
    public :
        void printPrimes(long long l, long long r);           //print primes from l to r
        long long printPrimeSum(long long l, long long r);    //sum all primes from l to r
};

class NumberAnalyzer{
    public :
        bool isSquareFree(long long x);   //check if the number x is divisible by any square number other than 1
        long long countDivisors(long long x);   //count divisors of x
        long long sumOfDivisors(long long x);   //sum all the divisors of x
};


int CurrencySorter::partition(vector<int> &v, int low, int high){
    int pivot = v[high];

    int i = low - 1;

    for(int j = low; j < high; j++){
        if(v[j] < pivot){
            i++;
            int t = v[i];
            v[i] = v[j];
            v[j] = t;
        }
    }

    int t = v[i + 1];
    v[i + 1] = v[high];
    v[high] = t;

    return i + 1;
}

void CurrencySorter::quickSort(vector<int> &v, int low, int high){
    if(low < high){
        int pIndex = partition(v, low, high);

        quickSort(v, low, pIndex - 1);
        quickSort(v, pIndex + 1, high);
    }
}


void CurrencySorter::operator() (vector<int> &v){
    quickSort(v, 0, v.size() - 1);
    for_each(v.begin(), v.end(), [](int x){cout << x << " ";});
    cout << "\n";
}


long long FibonacciGenerator::operator() (long long i){
    return fibCalc(i);
} 

void FibonacciGenerator::multiply(vector<long long> &A, vector<long long> &B){
    vector<long long> C(4);

    C[0] = ((A[0] * B[0]) % MOD + (A[1] * B[2]) % MOD) % MOD;
    C[1] = ((A[0] * B[1]) % MOD + (A[1] * B[3]) % MOD) % MOD;
    C[2] = ((A[2] * B[0]) % MOD + (A[3] * B[2]) % MOD) % MOD;
    C[3] = ((A[2] * B[1]) % MOD + (A[3] * B[3]) % MOD) % MOD; 

    A[0] = C[0];
    A[1] = C[1];
    A[2] = C[2];
    A[3] = C[3];
}

vector<long long> FibonacciGenerator::power(vector<long long> M, long long exp){
    vector<long long> ans = {1, 0 , 0, 1};

    while(exp){
        if(exp & 1){
            multiply(ans, M);
        }
        multiply(M, M);
        exp >>= 1;
    }
    return ans;
}

long long FibonacciGenerator::fibCalc(long long n){
    if(n == 0 || n == 1){
        return 1;
    }

    vector<long long> M = { 1, 1 , 1, 0 };

    vector<long long> F = { 1, 0, 0, 0 };

    vector<long long> res = power(M, n - 1);
    multiply(res, F);
    return res[0];
}

void PrimeCalculator::printPrimes(long long l, long long r){
    vector<char> isPrime(r - l + 1, true);
    for (long long i : primes){
        for (long long j = max(i * i, (l + i - 1) / i * i); j <= r; j += i){
            isPrime[j - l] = false;
        }
    }
    if (l == 1){
        isPrime[0] = false;
    }
    for(int i = 0; i < isPrime.size(); i++){
        if(isPrime[i]){
            cout << l + i << " ";
        }
    }
    cout << "\n";
}

long long PrimeCalculator::printPrimeSum(long long l, long long r){
    long long sum = 0;
    vector<char> isPrime(r - l + 1, true);
    for (long long i : primes){
        for (long long j = max(i * i, (l + i - 1) / i * i); j <= r; j += i){
            isPrime[j - l] = false;
        }
    }
    if (l == 1){
        isPrime[0] = false;
    }
    for(int i = 0; i < isPrime.size(); i++){
        if(isPrime[i]){
            sum += (l + i);
        }
    }
    return sum;
}

bool NumberAnalyzer::isSquareFree(long long x){
    for(int i = 0; i < (int)squares.size(); i++){
        if(squares[i] > x){
            break;
        }
        if(x % squares[i] == 0){
            return false;
        }
    }
    return true;
}

long long NumberAnalyzer::countDivisors(long long x){
    long long total = 1;
    for (int i = 2; (long long)i * i <= x; i++) {
        if (x % i == 0) {
            int e = 0;
            do {
                e++;
                x /= i;
            }while(x % i == 0);
            total *= e + 1;
        }
    }
    if (x > 1) {
        total *= 2;
    }
    return total;
}

long long NumberAnalyzer::sumOfDivisors(long long x){
    long long total = 1;

    for (int i = 2; (long long)i * i <= x; i++) {
        if (x % i == 0) {
            int e = 0;
            do{
                e++;
                x /= i;
            }while(x % i == 0);

            long long sum = 0, pow = 1;
            do{
                sum += pow;
                pow *= i;
            }while(e-- > 0);
            total *= sum;
        }
    }
    if (x > 1) {
        total *= (1 + x);
    }
    return total;
}

void precalcSieve(){
    for (long long i = 2; i < 1e6 + 10; ++i) {
        if (!sieve[i]) {
            primes.push_back(i);
            for (long long j = i * i; j < 1e6 + 10; j += i)
                sieve[j] = true;
        }
    }
}

void precalcSquare(){
    for(int i = 2; i < (int)(1e4 + 10); i++){
        squares.push_back(i * i);
    }
}

int main(){
    int tc;
    cin >> tc;
    if(tc == 1){
        int t;
        cin >> t;
        for(int i = 0; i < t; i++){
            int n; 
            cin >> n;
            vector<int> v(n);
            for(int j = 0; j < n; j++){
                cin >> v[j];
            }
            CurrencySorter currencySorter;
            currencySorter(v);
        }
    }else if(tc == 2){
        int t;
        cin >> t;
        for(int i = 0; i < t; i++){
            long long x;
            cin >> x;
            FibonacciGenerator fibonacciGenerator;
            cout << fibonacciGenerator(x) << "\n";
        }
    }else if(tc == 3){
        int t; 
        cin >> t;
        precalcSieve();
        for(int i = 0; i < t; i++){
            string s;
            long long l,  r;
            cin >> s >> l >> r; 
            PrimeCalculator primeCalculator;
            if(s == "printPrimes"){
                primeCalculator.printPrimes(l, r);
            }else if(s == "printPrimeSum"){
                cout << primeCalculator.printPrimeSum(l, r) << "\n";
            }else{
                assert(false);
            }
        }
    }else if(tc == 4){
        int t; 
        cin >> t;
        precalcSquare();
        for(int i = 0; i < t; i++){
            string s;
            int x;
            cin >> s >> x;
            NumberAnalyzer numberAnalyzer;
            if(s == "isSquareFree"){
                cout << (numberAnalyzer.isSquareFree(x) ? "yes" : "no") << "\n";
            }else if(s == "countDivisors"){
                cout << numberAnalyzer.countDivisors(x) << "\n";
            }else if(s == "sumOfDivisors"){
                cout << numberAnalyzer.sumOfDivisors(x) << "\n";
            }else{
                assert(false);
            }
        }
    }else{
        assert(false);
    }
}