#include <bits/stdc++.h>
#define DB cout<<"HERE\n"
using namespace std;

/*Comparator Functor for merge sort in rows*/
class Comparator{
    public :
        Comparator(bool increasing);            //constructor to initialize increasing or decreasing
        bool compare(int64_t n1, int64_t n2);   //comparing function
        void setBool(bool increasing);          //dynamic setting of comparator
   private :
        bool increasing;
};

/* Class holding information about the Quantum Board */
class Matrix{
    public :
        Matrix();
        void makeMatrix();
        void sortRows(Comparator &c);//function to sort the martix rows
        int64_t countInversions(Comparator &c);  //counting inversions 

        int64_t mergeSort(vector<int64_t> &v, int low, int high, Comparator &c);     //merge sort subroutine
        int64_t merge(vector<int64_t> &v, int low, int mid, int high, Comparator &c);//merge step of merge sort

        void display(); //printing the matrix
    private :
        int size;                       //size of the matrix
        vector<vector<int64_t>> board;  //board
};


/* Utility class holding points and its initial position*/
class Trip{
    public :
        Trip();
        Trip(int64_t x, int64_t y, int pos);

        int64_t x;      //x coordinate of the point
        int64_t y;      //y coordinate of the point
        int pos;        //position it arrived in
};

/* Space class to represent coordinates of all players */
class Space{
    public :
        Space(int size); //Constructor initializing the number of players and their coordinates

        pair<Trip, Trip> closestPair();                         //finding the closest pair
        int64_t findDistanceSquared(Trip p1, Trip p2);          //utility function to find distance between two points
        pair<Trip, Trip> getMinimumDistance(vector<Trip> Px);   //recursive subroutine
        pair<Trip, Trip> baseCase(vector<Trip> Px);             //base case of the closest pair
        pair<Trip, Trip> stripCase(vector<Trip> strip, int64_t min_d, pair<Trip, Trip> mn); //delta line case on either side of mid
        pair<Trip, Trip> tieBreaker(pair<Trip, Trip> p1, pair<Trip, Trip> p2);              //tie breaking rules
    private :
        int size;
        vector<Trip> coordinates;
};

Comparator::Comparator(bool increasing){
    this->increasing = increasing;
}

void Comparator::setBool(bool increasing){
    this->increasing = increasing;
}

bool Comparator::compare(int64_t n1, int64_t n2){
    return (increasing ? n1 <= n2 : n1 >= n2);
}

Matrix::Matrix(){

}


void Matrix::makeMatrix(){
    int size;
    cin >> size;
    this->size = size;
    this->board.resize(this->size, vector<int64_t>(this->size));
    for(int i = 0; i < (int)this->board.size(); i++){
        for(int j = 0; j < (int)this->board.size(); j++){
            int64_t p;
            cin >> p;
            this->board[i][j] = p;
        }
    }
}

void Matrix::sortRows(Comparator &c){
    for(int i = 0; i < (int)this->board.size(); i++){
        mergeSort(this->board[i], 0, this->board.size() - 1, c);
    }
}

int64_t Matrix::countInversions(Comparator &c){
    vector<int64_t> flat;
    for(int i = 0; i < (int)this->board.size(); i++){
        for(int j = 0; j < (int)this->board.size(); j++){
            flat.push_back(this->board[i][j]);
        }
    }
    return mergeSort(flat, 0, flat.size() - 1, c);
}

int64_t Matrix::mergeSort(vector<int64_t> &v, int low, int high, Comparator &c){
    int64_t ret = 0;
    if(low < high){
        int mid = (low + high) / 2;
        int64_t l1 = mergeSort(v, low, mid, c);
        int64_t l2 = mergeSort(v, mid + 1, high, c);
        int64_t l3 = merge(v, low, mid, high, c);
        ret = l1 + l2 + l3;
    }
    return ret;
}

int64_t Matrix::merge(vector<int64_t> &v, int low, int mid, int high, Comparator &c){
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int64_t> L(n1); vector<int64_t> R(n2);
    for(int i = 0; i < n1; i++){
        L[i] = v[i + low];
    }

    for(int i = 0; i < n2; i++){
        R[i] = v[i + mid + 1];
    }

    int i = 0; int j = 0; int k = low;
    int64_t inversions = 0;
    while(i < n1 && j < n2){
        if(c.compare(L[i], R[j])){
            v[k++] = L[i++];
        }else{
            inversions += n1 - i;
            v[k++] = R[j++];
        }
    }

    while(i < n1){
        v[k++] = L[i++];
    }

    while(j < n2){
        v[k++] = R[j++];
    }
    return inversions;
}

void Matrix::display(){
    for(int i = 0; i < (int)this->board.size(); i++){
        for(int j = 0; j < (int)this->board.size(); j++){
            cout << this->board[i][j] << " ";
        }
        cout << "\n";
    }
}

Trip::Trip(){

}

Trip::Trip(int64_t x, int64_t y, int pos){
    this->x = x;
    this->y = y;
    this->pos = pos;
}

Space::Space(int size){
    this->size = size;
    for(int i = 0; i < (int)this->size; i++){
        int64_t x, y;
        cin >> x >> y;
        Trip p(x, y, i);
        coordinates.push_back(p);
    }
}

pair<Trip, Trip> Space::closestPair(){
    vector<Trip> Px; 

    for(int i = 0; i < (int)this->coordinates.size(); i++){
        Px.push_back(this->coordinates[i]);
    }
    sort(Px.begin(), Px.end(), [](Trip a, Trip b){
        return a.x < b.x;
    });

    pair<Trip, Trip> p = getMinimumDistance(Px);
    return p;
}

int64_t Space::findDistanceSquared(Trip p1, Trip p2){
    return ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y));
}

pair<Trip, Trip> Space::getMinimumDistance(vector<Trip> Px){
    if((int)Px.size() <= 3){
        return baseCase(Px);
    }

    int mid = (int)(Px.size() / 2);
    vector<Trip> Qx;
    vector<Trip> Rx;

    for(int i = 0; i < mid; i++){
        Qx.push_back(Px[i]);
    }
    for(int i = mid; i < (int)Px.size(); i++){
        Rx.push_back(Px[i]);
    }

    pair<Trip, Trip> q = getMinimumDistance(Qx);
    pair<Trip, Trip> r = getMinimumDistance(Rx);
    
    pair<Trip, Trip> mn = tieBreaker(q, r);
    int64_t min_d = findDistanceSquared(mn.first, mn.second);

    vector<Trip> strip;
    Trip midpt = Px[mid];
    for(int i = 0; i < (int)Px.size(); i++){
        if(abs(Px[i].x - midpt.x) < min_d){
            strip.push_back(Px[i]);
        }
    }
    pair<Trip, Trip> mn_strip = stripCase(strip, min_d, mn);
    return mn_strip;
}

pair<Trip, Trip> Space::tieBreaker(pair<Trip, Trip> p1, pair<Trip, Trip> p2){
    int64_t d1 = findDistanceSquared(p1.first, p1.second);
    int64_t d2 = findDistanceSquared(p2.first, p2.second);
    if(d1 < d2){
        return p1;
    }else if(d1 > d2){
        return p2;
    }else{
        if(p1.first.x < p2.first.x){
            return p1;
        }else if(p1.first.x > p2.first.x){
            return p2;
        }else{
            if(p1.first.y < p2.first.y){
                return p1;
            }else if(p1.first.y < p2.first.y){
                return p2;
            }else{
                if(p1.second.x < p2.second.x){
                    return p1;
                }else if(p1.second.x > p2.second.x){
                    return p2;
                }else{
                    if(p1.second.y < p2.second.y){
                        return p1;
                    }else if(p1.second.y > p2.second.y){
                        return p2;
                    }else{
                        if(p1.first.pos < p2.first.pos){
                            return p1;
                        }else if(p1.first.pos > p2.first.pos){
                            return p2;
                        }else{
                            if(p1.second.pos < p2.second.pos){
                                return p1;
                            }else{
                                return p2;
                            }
                        }
                    }
                }
            }
        }
    }
}

pair<Trip, Trip> Space::stripCase(vector<Trip> strip, int64_t min_d, pair<Trip, Trip> mn){
    sort(strip.begin(), strip.end(), [](Trip a, Trip b){
        return a.y < b.y;
    });

    pair<Trip, Trip> ret_min = mn;
    for(int i = 0; i < (int)strip.size(); i++){
        for(int j = i + 1; j < (int)strip.size() && j - i + 1 < 8; j++){
            if(strip[i].pos < strip[j].pos){
                ret_min = tieBreaker(ret_min, make_pair(strip[i], strip[j]));
            }else{
                ret_min = tieBreaker(ret_min, make_pair(strip[j], strip[i]));
            }
        }
    }

    return ret_min;
}

pair<Trip, Trip> Space::baseCase(vector<Trip> Px){
    int64_t mn = INT64_MAX;

    pair<Trip, Trip> ret_min;

    if(Px[0].pos < Px[1].pos){
        ret_min = make_pair(Px[0], Px[1]);
    }else{
        ret_min = make_pair(Px[1], Px[0]);
    }
    for(int i  = 0; i < (int)Px.size(); i++){
        for(int j = i + 1; j < (int)Px.size(); j++){
            if(Px[i].pos < Px[j].pos){
                ret_min = tieBreaker(ret_min, make_pair(Px[i], Px[j]));
            }else{
                ret_min = tieBreaker(ret_min, make_pair(Px[j], Px[i]));
            }
        }
    }

    return ret_min;
}

int main(){
    string s;
    cin >> s;
    Matrix m;
    Comparator comp(true);
    while(s != "END"){
        if(s == "CREATE_2D"){
            m.makeMatrix();
        }else if(s == "DISPLAY_2D"){
            m.display();
        }else if(s == "INVERSION_2D"){
            comp.setBool(true);
            int64_t inversions = m.countInversions(comp);
            cout << inversions << "\n";
        }else if(s == "SORT_2D"){
            string c;
            cin >> c;
            if(c == "ascending"){
                comp.setBool(true);
                m.sortRows(comp);
            }else{
                comp.setBool(false);
                m.sortRows(comp);
            }
        }else if(s == "CLOSEST_2D"){
            int n;
            cin >> n; 
            Space s(n);
            pair<Trip, Trip> points = s.closestPair();
            cout << points.first.x << " " << points.first.y << " " << points.second.x << " " << points.second.y << "\n";
        }else if(s == "END"){
            break;
        }else{
            assert(false);
        }
        cin >> s;
    }
}