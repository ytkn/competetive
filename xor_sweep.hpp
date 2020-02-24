#include <iostream>

using namespace std;
typedef long long ll;

long b[60];

void init(){
    long m = 1;
    for(int i = 0; i < 60; i++){
        b[i] = m;
        m = m<<1;
    }
}

void sweep(long A[], int N){
    int cur = 0;
    for(int i = 0; i < 60 && cur < N ; i++){
        if(!(A[cur]&b[59-i])){
            for(int j = cur; j < N; j++){
                if(A[j]&b[59-i]) {
                    swap(A[cur], A[j]);
                    break;
                }
            } 
        }
        if(A[cur]&b[59-i]){
            for(int j = 0; j < N; j++){
                if(j == cur) continue;
                if(A[j]&b[59-i]){
                    A[j] = A[j]^A[cur];
                }
            }
            cur++;
        }
    }
}