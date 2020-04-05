#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

vector<vector<int>> sweep(vector<vector<int>> v){
    int N = v.size();
    int cur = 0;
    for(int i = 0; i < N ; i++){
        if(v[cur][i] == 0){
            for(int j = cur; j < N; j++){
                if(v[j][i] != 0) {
                    swap(v[cur], v[j]);
                    break;
                }
            } 
        }
        if(v[cur][i] != 0){
            for(int j = 0; j < N; j++){
                if(j == cur) continue;
                if(v[j][i] != 0){
                    for(int k = 0; k < N; k++){
                        if(v[cur][i] == v[j][i]) v[j][k] -= v[cur][k];
                        else v[j][k] += v[cur][k];
                        v[j][k] = (v[j][k]+2)%2;
                    }
                }
            }
            cur++;
        }
    }
    return v;
}