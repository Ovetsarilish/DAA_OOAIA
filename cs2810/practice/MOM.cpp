#include <bits/stdc++.h>

using namespace std;
void printVector(vector<int> v){
    for(int i = 0; i < (int)v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}
int bruteForceMedian(vector<int> v){
    sort(v.begin(), v.end());
    int mid = (int)v.size() / 2;
    return v[mid];
}
int partition(vector<int> &v, int low, int high, int median){
    int medianIndex = low;
    for(int i = low; i <= high; i++){
        if(v[i] == median){
            medianIndex = i; break;
        }
    }
    vector<int> L; vector<int> R;
    for(int i = low; i <= (int)high; i++){
        if(i != medianIndex){
            if(v[i] < v[medianIndex]){
                L.push_back(v[i]);
            }else{
                R.push_back(v[i]);
            }
        }
    }
    int rank = (int)L.size() + low;
    for(int i = 0; i < (int)L.size(); i++){
        v[i + low] = L[i];
    }
    v[rank] = median;
    for(int i = 0; i < (int)R.size(); i++){
        v[i + rank + 1] = R[i];
    }
    return rank;
}
int MOMSelect(vector<int> &v, int l, int r, int k){
    vector<int> tempMedians;
    for(int i = 0; i < (int)v.size(); i += 5){
        vector<int> tmp;
        for(int j = i; j < min((int)v.size(), i + 5); j++){
            tmp.push_back(v[j]);
        }
        tempMedians.push_back(bruteForceMedian(tmp));
    }
    int median = tempMedians.size() == 1 ? tempMedians[0] : MOMSelect(tempMedians, 0, (int)tempMedians.size() - 1, (int)tempMedians.size() / 2);
    int rank = partition(v, l, r, median);
    if(rank == k - 1){
        return v[rank];
    }else if(rank > k - 1){
        vector<int> v1;
        for(int i = 0; i < rank; i++){
            v1.push_back(v[i]);
        }
        return MOMSelect(v1, 0, v1.size() - 1, k);
    }else{
        vector<int> v1;
        for(int i = rank + 1; i < (int)v.size(); i++){
            v1.push_back(v[i]);
        }
        return MOMSelect(v1, 0, (int)v1.size() - 1, k - rank - 1);
    }
}

int main(){
    vector<int> v = { 1, 3, 4, 2, 7, 5, 8, 6 };
    int p = MOMSelect(v, 0, (int)v.size() - 1, 6);
    cout << p << "\n";
}