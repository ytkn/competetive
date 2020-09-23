#include <vector>
#include "scc.hpp"

using namespace std;

class TwoSat{
    public:
        TwoSat(int n) : scc(2*n) {
            N = n;
        }

        void add_clause(int i, bool f, int j, bool g) {
            scc.add_edge(vertex_index(i, !f), vertex_index(j, g));
            scc.add_edge(vertex_index(j, !g), vertex_index(i, f));
        }

        bool satisfiable(){
            scc.scc();
            for(int i = 0; i < N; i++){
                if(scc.idx[vertex_index(i, true)] == scc.idx[vertex_index(i, false)]) return false;
            }
            return true;
        }

        vector<bool> answer(){
            vector<bool> ret(N, false);
            for(int i = 0; i < N; i++){
                int dif = scc.idx[vertex_index(i, true)] - scc.idx[vertex_index(i, false)]; 
                if(dif == 0) throw "not satisfiable";
                // true => falseなのでfalse
                if(dif < 0){
                    ret[i] = false;
                // false => trueなのでtrue                
                }else{
                    ret[i] = true;
                }
            }
            return ret;
        }

    private:
        Scc scc;
        int N;
        // true -> i, false -> i+N
        int vertex_index(int i, bool f){
            return f ? i : i+N;
        }
};