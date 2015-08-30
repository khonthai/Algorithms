#include<stdio.h>
#include<vector>
#include<algorithm>
#define MAX_N 100000
#define B 1000

using namespace std;
int a[MAX_N];
int num[MAX_N];
vector<int> bucket[MAX_N/B];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        num[i] = a[i];
        bucket[i/B].push_back(num[i]);
    }
    sort(num, num+n);
    for (int i = 0; i < n/B; i++) {
        sort(bucket[i].begin(), bucket[i].end());
    }
    int i, j, k;
    for (int t = 0; t < m; t++) {
        scanf("%d%d%d", &i, &j, &k);
        i--;
        int lb = -1;
        int ub = n-1;
        while(ub - lb > 1){
            int mid = (lb+ub)/2;
            int x = num[mid];
            int tl = i, tr = j, c = 0;
            while (tr > tl && tl%B != 0) {
                if (a[tl++] <= x) {
                    c++;
                }
            }
            while (tr > tl && tr%B != 0) {
                if (a[--tr] <= x ) {
                    c++;
                }
            }
            while (tl < tr) {
                int b = tl/B;
                c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
                tl += B;
            }
            if (c >= k) {
                ub = mid;
            }else{
                lb = mid;
            }
        }
        printf("%d\n", num[ub]);
    }
    return 0;
}
