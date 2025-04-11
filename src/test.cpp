#include <iostream>
#include <string>

using namespace std;

int main(){

    string s;

    getline(cin,s);

    cout << s[s.size()-1];

    return 0;
}