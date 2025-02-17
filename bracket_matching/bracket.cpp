#include<bits/stdc++.h>
using namespace std;

int main() {

#ifndef ONLINE_JUDGE
    // For getting input from input.txt file 
    freopen("input.txt", "r", stdin); 

    // Printing the Output to output.txt file 
    freopen("output.txt", "w", stdout); 
#endif

    int t;
    cin >> t;

    string array[t];
    string resArray[t];

    for (int i=0; i<t; i++) {
        string brackets;
        cin >> brackets;
        array[i] = brackets;
    }
    
    // stack<char> oBrackets;

    for(int i=0;i<t; i++) {
        stack<char> cBrackets;
        string input = array[i];

        bool ok = true;

        for(char c:input) {
            if(c == '(' || c == '{' || c == '[') {
                cBrackets.push(c);   
            } else {
                if(cBrackets.size() <=0) {
                    ok=false;
                    break;
                }
                char closest = cBrackets.top();
                bool match = false;
                if(closest == '(') {
                    if(c == ')') {
                        match=true;
                    }
                } else if(closest == '{') {
                    if(c == '}') {
                        match=true;
                    }
                } else if(closest == '[') {
                    if(c == ']') {
                        match=true;
                    }
                }

                if(match==true) {
                    cBrackets.pop();
                } else {
                    ok=false;
                    break;
                }
            }
        }
        if(ok == true && cBrackets.size() == 0) {
            resArray[i] = "YES";
        } else {
            resArray[i] = "NO";
        }
    }

    for(string res:resArray) {
        cout << res << endl;
    }

    return 0;
}