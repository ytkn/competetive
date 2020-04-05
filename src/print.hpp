template <typename T>
void print(T array){
    for(auto iter = array.begin(); iter != array.end(); iter++){
        cout << *iter;
        if(iter+1 == array.end()) cout << endl;
        else cout << ' ';
    }
}