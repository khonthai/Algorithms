#include<iostream>
#include<stdio.h>
#include<string.h>
#define M 15
#define N 15
using namespace std;
int m, n;

int x[5] = {-1, 0,0, 0 ,1 };
int y[5] = {0,-1, 0, 1, 0 };
int ans[M][N];
int flip[M][N];
int tile[M][N];
int res = -1;
int res1 = 0;
int opt[M][N];

bool whilteOrNot(int i, int j){
    if ((tile[i][j] + flip[i][j])%2 == 0) {
        return true;
    }else{
        return false;
    }
}

int cal(){
    int a = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (whilteOrNot(i-1, j) == false) {
                //if i-1, j is black
                ans[i][j] = 1;
                a++;
                for (int k = 0; k < 5; k++) {
                    int x2 = i+x[k];
                    int y2 = j+y[k];
                    if (x2 >= 0 && x2 < m && y2 >= 0 && y2 < n) {
                        flip[x2][y2]++;
                    }
                }
            }
        }
    }
    return a;
}

bool check(){
    for (int i = 0; i < n; i++) {
        if ((tile[m-1][i]+flip[m-1][i])%2!=0) {
            return false;
        }
    }
    return true;
}



int main(){
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &tile[i][j]);
        }
    }
    for (int i = 0; i < 1 << n; i++) {
        memset(flip, 0, sizeof(flip));
        res1 = 0;
        for (int j = 0; j < n; j++) {
            int a = n-1-j;
            int b = i >> j & 1;
            ans[0][a] = b;
            if (b == 1) {
                res1++;
                for (int k = 0; k < 5; k++) {
                    int x2 = 0+x[k];
                    int y2 = a+y[k];
                    if (x2 >= 0 && x2 < m && y2 >= 0 && y2 < n) {
                        flip[x2][y2]++;
                    }
                }
            }
        }
        res1 += cal();
        if (check()==true && (res1 < res||res < 0)) {
            res = res1;
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < n; k++) {
                    opt[j][k] = ans[j][k];
                    ans[j][k] = 0;
                }
            }
        }
    }
    if (res < 0) {
        cout << "IMPOSSIBLE" << endl;
    }else{
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                printf("%d%c", opt[j][k], k+1==n ? '\n' : ' ');
            }
        }
    }
    return 0;
}