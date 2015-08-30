#include<stdio.h>
typedef long long ll;

ll pow(ll x, ll n){
    ll ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = ans * x;
        }
        x = x * x;
        n >>= 1;
    }
    return ans;
}

ll getPar(ll n){
    ll res = 0;
    for (int i = 0; i*2 <= n; i++) {
        ll left = n-i*2;
        res += pow(2, left);
    }
    return res;
}


int main(){
    int n;
    scanf("%d", &n);
    ll ans = 0;
    for (int i = 0; i*2 <= n; i++) {
        ans += getPar(n-i*2);
    }
    printf("%lld\n", ans);
    return 0;
}