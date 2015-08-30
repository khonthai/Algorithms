#include<iostream>
#define MAX_N 10000
using namespace std;
int a[MAX_N];
int bit[MAX_N];
int n;

void init(){
    for (int i = 0; i < n+1; i++) {
        bit[i] = 0;
    }
}

int sum(int i){
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}
void add(int i, int x){
    while (i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}


int main(){
    int ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    init();
    for (int j = 0; j < n; j++) {
        cout << " j = " << j << endl;
        for (int k = 1; k <=n; k++) {
            cout << bit[k] << " " ;
        }
        cout << "sum (a[i])" << sum(a[j]) << endl;
        ans += j-sum(a[j]);
        add(a[j], 1);
        
        cout << ans << endl;
        
    }
    cout << ans << endl;
    return 0;
}
