#include<iostream>
#include<algorithm>
using namespace std;
#define N 1000

int main(){
    int n, R;
    int x[N];
    while (1) {
        cin >> R >> n;
        if (n == -1 && R == -1) {
            break;
        }
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        sort(x, x+n);
        int i = 0;
        int prev = 0;
        int ans = 0;
        while (i < n) {
            prev = x[i++];
            while (i < n && x[i] - prev <= R) {
                i++;
            }
            prev = x[i-1];
            while (i < n && x[i] - prev <= R) {
                i++;
            }
            ans++;
        }
        cout << ans << endl;
    }
    return 0;
}