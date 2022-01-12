#include "binary_trie.hpp"
#include <set>

#include "generator_utils.cpp"

#include "gtest/gtest.h"

class NaiveMinMaxXor{
    public:
    NaiveMinMaxXor(){}
    int max_xor(int x){
        int ans = 0;
        for(int a: values) ans = max(ans, x^a);
        return ans;
    }
    int min_xor(int x){
        int ans = 2e9;
        for(int a: values) ans = min(ans, x^a);
        return ans;
    }
    void add(int x){
        values.insert(x);
    }
    void erase(int x){
        if(values.count(x)) values.erase(x);
    }
    private:
    set<int> values;
};

TEST(binary_trie, min_and_max) {
    auto naive = NaiveMinMaxXor();
    auto trie = BinaryTrie<int, 30>();
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 3; j++) {
            int x = randint(0, 10000);
            naive.add(x);
            trie.add(x);
        }
        int x = randint(0, 10000);
        ASSERT_EQ(naive.min_xor(x), trie.min_xor(x));
        ASSERT_EQ(naive.max_xor(x), trie.max_xor(x));
        for(int j = 0; j < 2; j++){
            int x = randint(0, 10000);
            naive.erase(x);
            trie.erase(x);
        }
    }
}