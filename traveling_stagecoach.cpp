#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define MAX_N 8
#define MAX_M 30
#define INF 1e9 + 7
int d[MAX_M][MAX_M];
double dp[1<<MAX_N][MAX_M];
int t[MAX_N];

int main(){
    int n,m, a, b, p;
    while(scanf("%d%d%d%d%d", &n, &m, &p, &a, &b) != EOF && n > 0){
        for (int i = 0; i < n; i++) {
            scanf("%d", &t[i]);
        }
        memset(d, -1, sizeof(d));
        int x, y, z;
        for (int i = 0; i < p; i++) {
            scanf("%d%d%d", &x, &y, &z);
            x--;
            y--;
            d[x][y] = z;
            d[y][x] = z;
        }
        for (int i = 0; i < 1 <<n; i++) {
            fill(dp[i], dp[i]+m, INF);
        }
        dp[(1<<n)-1][a-1] = 0.0;
        
        double res = INF;
        for (int S = (1<<n)-1; S >= 0; S--) {
            res = min(res, dp[S][b-1]);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (S>>j&1) {
                        for (int u = 0; u < m; u++) {
                            if(d[i][u] > -1){
                                dp[S & ~(1<<j)][u] = min(dp[S & ~(1<<j)][u], dp[S][i]+(double)d[i][u]/(double)t[j]);
                            }
                        }
                    }
                }
            }
        }
        if (res == INF) {
            printf("Impossible\n");
        }else{
            printf("%.3f\n", res);
        }
    }
    return 0;
}