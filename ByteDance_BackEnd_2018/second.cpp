#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
bool checkIfValid(vector<int>& temp, const int& m){
    // loop
    int len = temp.size();
    for(int i=0; i<len; i++){
        int summ = 0;
        int start = i, count = 1;
        while(count <= m){
            if(start >= len) start %= len;
            summ += temp[start];
            start++;
            count++;
        }
        if(summ >= 2) return false;
    }
    return true;
}

int main(){
    // get n, m, c
    int n, m, c;
    cin>>n>>m>>c;
    
    // get color situation
    unordered_map<int, vector<int>> mp;
    for(int i=0; i<n; i++){
        // get how many colors
        int number;
        cin>>number;
        if(number == 0) continue;
        
        // loop for each ball
        for(int j=0; j<number; j++){
            int color;
            cin>>color;
            if(mp.find(color) != mp.end()) mp[color][i] = 1;
            else{
                vector<int> temp(n, 0);
                temp[i] = 1;
                mp[color] = temp;
            }
        }
    }
    
    // loop with the map
    int result = 0;
    for(auto it = mp.begin(); it != mp.end(); it++){
        if(!checkIfValid(it->second, m)) result++;
    }
    cout<<result<<"\n";
    
    return 0;
}