#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 4000
int a[N], b[N], c[N], d[N];
int CD[N*N+1];

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            CD[i*n+j] = c[i]+d[j];
        }
    }
    sort(CD, CD+n*n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int tmp = -(a[i]+b[j]);
            ans += upper_bound(CD, CD+n*n, tmp) - lower_bound(CD, CD+n*n, tmp);
        }
    }
    printf("%lld\n", ans);
    return 0;
}