#include<iostream>
#include<stdio.h>
#include<string.h>
#define M 15
#define N 15
using namespace std;
int m, n;

int x[5] = {-1, 0,0, 0 ,1 };
int y[5] = {0,-1, 0, 1, 0 };
int flip[M][N];
int tile[M][N];
int res = -1;
int opt[M][N];

bool whilteOrNot(int i, int j){
    int c = tile[i][j];
    for (int k = 0; k < 5; k++) {
        int x2 = i+x[k], y2 = j+y[k];
        if (x2 >= 0 && x2 < m && y2 >= 0 && y2 < n) {
            c += flip[x2][y2];
        }
    }
    return c%2;
}

int cal(){
    int a = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (whilteOrNot(i-1, j) != 0) {
                flip[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (whilteOrNot(m-1, i) != 0) {
            return -1;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (flip[i][j] == 1) {
                a++;
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
        for (int j = 0; j < n; j++) {
            int a = n-1-j;
            int b = i >> j & 1;
            flip[0][a] = b;
        }
        int num = cal();
        if (num >= 0 && (num < res || res < 0)) {
            res = num;
            memcpy(opt, flip, sizeof(flip));
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