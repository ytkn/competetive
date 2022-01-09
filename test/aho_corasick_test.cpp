#include "aho_corasick.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

int simple_search(string text, string key_word){
    int n = text.size();
    int m = key_word.size();
    int ans = 0;
    for(int i = 0; i+m <= n; i++){
        for(int j = 0; j < m; j++){
            if(text[i+j] != key_word[j]){
                break;
            }
            if(j+1 == m) ans++;
        }
    }
    return ans;
}

string gen_str(int len, int n_chars){
    string ans;
    for(int i = 0; i < len; i++){
        ans += randint(0, n_chars)+'a';
    }
    return ans;
}

void test(int n_chars, int text_len){
    auto text = gen_str(text_len, n_chars);
    vector<string> key_words;
    for(int i = 0; i < 100; i++){
        key_words.push_back(gen_str(randint(2, 10), n_chars));
        key_words.push_back(gen_str(randint(10, 40), n_chars));
    }
    int n = key_words.size();
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        v[i] = simple_search(text, key_words[i]);
    }
    auto ac = AhoCorasick(key_words);
    auto u = ac.search_text(text);
    
    for(int i = 0; i < n; i++){
        ASSERT_EQ(u[i], v[i]);
    }
}

TEST(aho_corasick, search) {
    test(1, 1000);
    for(int i = 0; i < 10; i++) {
        test(2, 1000);
        test(3, 1000);
        test(4, 1000);
        test(26, 1000);
    }
}
