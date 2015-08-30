#include<iostream>
using namespace std;
#define MAX_N 1000
#define M 1000000000
char a[MAX_N][MAX_N];
int remain, n;
int ans = 0;
int x[2] = {1, 0};
int y[2] = {0, 1};

//void print(){
//    cout << "-----------"<< endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << a[i][j];
//        }
//        cout << " | ";
//        for (int j = 0; j < n; j++) {
//            cout << used[i][j];
//        }
//        cout << endl;
//    }
//    cout << "-----------"<< endl;
//}

//void dfs(int i, int j){
//    used[i][j] = true;
//    for (int k = 0; k < 2; k++) {
//        int ni = i+x[k], nj = j+y[k];
//        if (ni >= 0 && ni < n && nj >= 0 && nj < n && a[ni][nj] == '.') {
//            a[i][j] = 'x';
//            a[ni][nj] = 'x';
//            print();
//            remain -= 2;
//            if (remain == 0) {
//                ans++;
//            }else{
//                for (int l = 0; l < n; l++) {
//                    for (int m = 0; m < n; m++) {
//                        if (a[l][m] == '.' && !used[l][m]) {
//                            dfs(l, m);
//                        }
//                    }
//                }
//            }
//            a[i][j] = '.';
//            a[ni][nj] = '.';
//            remain += 2;
//            used[i][j] = false;
//
//        }
//    }
//}


int rec(int i, int j, bool used[MAX_N][MAX_N]){
    cout << i << endl;
    if (j == n) {
        return rec(i+1, 0, used);
    }
    if (i == n) {
        cout << "here" << endl;
        return 1;
    }
    if (used[i][j] || a[i][j]=='x') {
        return rec(i, j+1, used);
    }
    int res = 0;
    used[i][j] = true;
    if (j+1 < n && !used[i][j+1] && a[i][j+1] == '.') {
        used[i][j+1] = true;
        cout << "here1" << endl;

        res += rec(i, j+1, used);
        used[i][j+1] = false;
    }
    if (i+1 < n && !used[i+1][j] && a[i+1][j] == '.') {
        used[i+1][j] = true;
        cout << "here2" << endl;

        res += rec(i, j+1, used);
        used[i+1][j] = false;
    }
    used[i][j] = false;
    return res % M;
}


int main(){
    cin >> n;
    int si, sj;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }
    //dfs(si, sj);
    bool used[MAX_N][MAX_N];
    memset(used, 0, sizeof(used));
    cout << rec(0, 0, used) << endl;
    return 0;
}