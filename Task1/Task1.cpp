#include <iostream>
#include <string>

using namespace std;
int main() {
    string s = "Hi mY frIend";
    string t = s;
    char c;
    bool b;
    int is = 0;
    
    while(is < s.size()){
    int ic = 0;
    b = false;
    while(ic < s.size()){
    if (tolower(s[is]) == tolower(s[ic]) && is != ic ){
    b = true;
    }
    ic++;  
    }
    if (b == true){
    t[is] = ')';
    }
    else{
    t[is] = '(';
    }
    is++;
    }
    
    cout << t;
    return 0;
}