#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

int main(){
    int p;
    cin >> p;
    int a[p];
    map<int, int> b;
    int n = 0;
    for (int i = 0; i < p; i++) {
        scanf("%d", &a[i]);
        if (b[a[i]] == 0) {
            n++;
        }
        b[a[i]]++;
    }
    int s = 0;
    int t = 0;
    int ans = p;
    int num = 0;
    b.clear();
    for (; ; ) {
        while (t < p && num < n) {
            if (b[a[t]] == 0) {
                num++;
            }
            b[a[t++]]++;
        }
        if (num < n) {
            break;
        }
        while (b[a[s]] > 1) {
            b[a[s]]--;
            s++;
        }
        ans = min(ans, t-s);
        b[a[s++]]--;
        num--;
    }
    cout << ans << endl;
    return 0;
}