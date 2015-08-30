#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define MAX_Y 12
#define MAX_X 12
#define MAX_V 244
char dat[MAX_Y][MAX_X];
vector<int> dX, dY;
vector<int> pX, pY;
int d[MAX_Y][MAX_X][MAX_Y][MAX_X];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int X, Y;
int V;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int i, int u){
    G[i].push_back(u);
    G[u].push_back(i);
}

bool dfs(int i){
    used[i] = true;
    for (int j = 0; j < G[i].size(); j++) {
        int u = G[i][j], w = match[u];
        if (w < 0 || (!used[w] && dfs(w))) {
            match[i] = u;
            match[u] = i;
            return true;
        }
    }
    return false;
}



int bipartite_matching(){
    int res = 0;
    for (int i = 0; i < V; i++) {
        if (match[i] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(i)) {
                res++;
            }
        }
    }
    return res;
}
bool C(int t){
    int door = dX.size(), people = pX.size();
    cout << door << " " << people << endl;
    for (int i = 0; i < t*door+people; i++) {
        G[i].clear();
    }
    for (int i = 0; i < door; i++) {
        for (int j = 0; j < people; j++) {
            if (d[dY[i]][dX[i]][pY[j]][pX[j]] >= 0) {
                for (int k = d[dY[i]][dX[i]][pY[j]][pX[j]]; k <= t; k++) {
                    add_edge((k-1)*door+i, t*door+j);
                    if (t == 12) {
                        cout << "left " << (k-1)*door+i << " right " << t*door+j<< endl;
                    }
                }
            }
        }
    }
    memset(match, -1, sizeof(match));
    return bipartite_matching() == people;
}




void bfs(int x, int y){
    queue<int> qx, qy;
    qx.push(x);
    qy.push(y);
    int depth = 0;
    int current = 1;
    int next = 0;
    while(!qx.empty()){
        int nx = qx.front();
        qx.pop();
        int ny = qy.front();
        qy.pop();
        current--;
        if(dat[ny][nx] == '.'){
            d[y][x][ny][nx] = depth;
            //cout << "hello" << endl;
            //cout << x << " " << y << " " << nx << " " << ny << endl;
        }
        for(int i = 0; i < 4; i++){
            int nextx = nx+dx[i], nexty = ny+dy[i];
            if (nextx >= 0 && nextx < X && nexty >= 0 && nexty < Y ){
                if(dat[nexty][nextx] == '.' && d[y][x][nexty][nextx] < 0){
                    qx.push(nextx);
                    qy.push(nexty);
                    next++;
                }
            }
        }
        if(current == 0){
            current = next;
            next = 0;
            depth++;
        }
    }
}


int main(){
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d%d", &Y, &X);
        memset(d, -1, sizeof(d));
        //cout << X << " " << Y;
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < X; k++) {
                cin >> dat[j][k];
            }
            //cout << endl;
            for (int k = 0; k < X; k++) {
                //cout << dat[j][k];
            }
        }
        //cout << "out "<< endl;
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < X; k++) {
                if (dat[j][k] == 'D') {
                    dX.push_back(k);
                    dY.push_back(j);
                    bfs(k, j);
                }else if(dat[j][k] == '.'){
                    pX.push_back(k);
                    pY.push_back(j);
                }
            }
        }
        int n = X*Y;
        int lb = -1;
        int ub = n+1;
        while (ub - lb > 1) {
            int mid = (lb+ub)/2;
            cout << lb <<" " << ub << " " << mid << endl;
            if(C(mid)) ub = mid;
            else lb = mid;
        }
        if (ub > n) {
            cout << "Impossible"<< endl;
        }else{
            cout << ub<< endl;
        }
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < X; k++) {
                if(dat[j][k] == 'D'){
                    cout << "door " << j << " " << k << endl;
                    for (int l = 0; l < Y; l++) {
                        for (int m = 0; m < X; m++) {
                            if(dat[l][m] == '.'){
                                cout << d[j][k][l][m];
                            }else{
                                cout << dat[l][m];
                            }
                        }
                        cout << endl;
                    }
                }
                cout << endl;
            }
        }
        
    }
    return 0;
}
