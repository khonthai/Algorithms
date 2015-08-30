#include<iostream>
#include<string.h>
using namespace std;
#define N 5000
bool f[N];
int dir[N];
int n;

int cal(int k){
    memset(f, 0, sizeof(f));
    int sum = 0;
    int ans = 0;
    for (int i = 0; i <= n-k; i++) {
        if ((dir[i]+sum)%2==1) {
            ans++;
            f[i] = 1;
        }
        sum += f[i];
        if (i-k+1 >= 0) {
            sum -= f[i-k+1];
        }
    }
    for (int i = n-k+1; i < n; i++) {
        if ((dir[i]+sum)%2==1) {
            return -1;
        }
        if (i-k+1 >= 0) {
            sum -= f[i-k+1];
        }
    }
    return ans;
}




int main(){
    cin >> n;
    char c;
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == 'B') {
            dir[i] = 1;
        }else{
            dir[i] = 0;
        }
    }
    int res = n;
    int res2 = 1;
    for (int i = 1; i <= n; i++) {
        int tmp = cal(i);
        if (tmp >= 0 &&tmp < res) {
            res = tmp;
            res2 = i;
        }
    }
    cout << res2 << " " << res << endl;
    return 0;
}