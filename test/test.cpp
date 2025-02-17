#include<bits/stdc++.h>

const int N=1e7;

int arr[N];
int arr2[N];

int main() {
    #ifndef ONLINE_JUDGE:
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    long long count = 3000000000;
    int len = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < count; i++){
        if(i<len) {
            arr[i]=2;
        } else {
            arr[3]=2;
        }
    }
    
    return 0;
}