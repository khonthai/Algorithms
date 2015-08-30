#include<iostream>
using namespace std;
#define MAX 100
int n, m;
char lake[MAX][MAX];
int v[4] = {-1, 0, 1};


void dfs(int i, int j){
    if (i >= n || i < 0 || j >= m || j < 0) {
        return;
    }
    if (lake[i][j] == 'W') {
        lake[i][j] = '.';
        for (int k = 0; k < 3; k++) {
            for (int l = 0; l < 3; l++) {
                dfs(i+v[k], j+v[l]);
            }
        }
    }else{
        return;
    }
}


int main(){
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> lake[i][j];
        }
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lake[i][j] == 'W') {
                dfs(i,j);
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}
