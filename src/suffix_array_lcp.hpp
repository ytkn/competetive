#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class SuffixArray{
    public:
        vector<int> rank;
        vector<int> sa;
        vector<int> lcp;
        string S;
        int n;
        SuffixArray(string _S){
            S = _S;
            n = _S.size();
            rank = vector<int>(n+1);
        }
        void construct_sa(){
            sa = vector<int>(n+1);
            vector<int> buf(n+1);
            for(int i = 0; i <= n; i++){
                sa[i] = i;
                rank[i] = i < n ? S[i] : -1;
            }

            for(int k = 1; k <= n; k *= 2){
                sort(sa.begin(), sa.end(), [&, k](int i, int j){
                    return compare_sa(i, j, k);
                });

                buf[sa[0]] = 0;
                for(int i = 1; i <= n; i++){
                    buf[sa[i]] = buf[sa[i-1]] + (compare_sa(sa[i-1], sa[i], k) ? 1 : 0);
                }
                for(int i = 0; i <= n; i++) rank[i] = buf[i];
            }
        }

        // sa is initlally constructed
        void construct_lcp(){
            lcp = vector<int>(n+1);

            int h = 0;
            lcp[0] = 0;
            for(int i = 0; i < n; i++){
                int j = sa[rank[i]-1];

                if(h > 0) h--;
                while(j+h < n && i+h < n){
                    if(S[i+h] != S[j+h]) break;
                    h++;
                }
                lcp[rank[i]-1] = h;
            }
        }
        
        void construct_both(){
            construct_sa();
            construct_lcp();
        }
    private:
        // (rank[i], rank[i+k]) vs (rank[j], rank[j+k])
        bool compare_sa(int i, int j, int k){
            if(rank[i] != rank[j]) return rank[i] < rank[j];
            else{
                int ri = i+k <= n ? rank[i+k] : -1;
                int rj = j+k <= n ? rank[j+k] : -1;
                return ri < rj;
            }
        }
};
