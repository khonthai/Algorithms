#include<stdio.h>
#include<algorithm>
using namespace std;
#define N 100000
int x[N];
int n;

bool ok(int m, int c){
    int prev = x[0];
    c--;
    for (int i = 1; i < n; i++) {
        if (x[i] - prev >= m) {
            prev = x[i];
            c--;
            if (c == 0) {
                return true;
            }
        }
    }
    return false;
}

int main(){
    int c;
    scanf("%d%d",&n, &c);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    sort(x, x+n);
    int lb = 1;
    int ub = (x[n-1]-x[0])/(c-1);
    int ans;
    while (lb <= ub) {
        int mid = (lb+ub)/2;
        if(ok(mid, c)){
            ans = mid;
            lb = mid+1;
        }else{
            ub = mid-1;
        }
    }
    printf("%d\n", ans);
    return 0;
}