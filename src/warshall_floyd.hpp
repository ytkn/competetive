#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll INF = 1e+15;

vector<vector<ll>> warshallfloyd(vector<vector<ll>> g){
    int n = g.size();
    vector<vector<ll>> dist(n, vector<ll>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dist[i][j] = g[i][j];
        }
        dist[i][i] = 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                ll new_len = dist[j][i] + dist[i][k];
                dist[j][k] = min(new_len, dist[j][k]);
            }
        }
    }
    return dist;
}