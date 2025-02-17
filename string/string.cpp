#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t;

    cin >> t;
    int arr[t];
    for (int i = 0; i < t; i++)
    {
        arr[i] = 0;
    }
    

    for (int i = 0; i < t; i++) {
        string line;
        cin >> line;

        int len = line.size();

        for(int j=0; j<len; j++) {
            if(line[j] == '1') {
                arr[i]++;  
            }
        }
    }

    for(int i=0; i<t; i++) {
        cout << arr[i] << endl;  
    }
    
    return 0;
}