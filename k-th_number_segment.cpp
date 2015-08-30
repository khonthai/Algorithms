#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int ST_SIZE = (1 << 18) -1;
#define MAX_N 100000
vector<int> dat[ST_SIZE];
int a[MAX_N];
int num[MAX_N];

void init(int k, int l, int r){
    if (r - l <= 1) {
        dat[k].push_back(a[l]);
    }else{
        int lch = k*2+1, rch = k*2+2, m = (l+r)/2;
        init(lch, l, m);
        init(rch, m, r);
        dat[k].resize(r-l);
        merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(), dat[k].begin());
    }
}
int query(int i, int j, int x, int k, int l, int r){
    if (j <= l || i >= r) {
        return 0;
    }else if(i <= l && j >= r){
        return upper_bound(dat[k].begin(),dat[k].end(),x)-dat[k].begin();
    }else{
        return query(i, j, x, k*2+1, l, (l+r)/2) + query(i, j, x, k*2+2, (l+r)/2, r);
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        num[i] = a[i];
    }
    sort(num, num+n);
    init(0, 0, n);
    int i, j, k;
    for (int t = 0; t < m; t++) {
        scanf("%d%d%d", &i, &j, &k);
        int lb = -1;
        int ub = n-1;
        i--;
        while(ub - lb > 1){
            int md = (ub+lb)/2;
            int c = query(i, j, num[md], 0, 0, n);
            if (c >= k) {
                ub = md;
            }else{
                lb = md;
            }
        }
        printf("%d\n", num[ub]);
    }
    return 0;
}
