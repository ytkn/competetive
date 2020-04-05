#include <iostream>

#define N_MAX 200

using namespace std;
typedef long long ll;
const ll INF = 1e+15;

void warshallfloyd(ll dist[N_MAX][N_MAX], ll edge[N_MAX][N_MAX], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dist[i][j] = edge[i][j];
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
}