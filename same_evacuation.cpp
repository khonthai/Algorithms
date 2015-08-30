#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define MAX_Y 12
#define MAX_X 12
#define MAX_V 1000
char field[MAX_X][MAX_Y+1];
vector<int> dX, dY;
vector<int> pX, pY;
int dist[MAX_X][MAX_Y][MAX_X][MAX_Y];
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
    memset(match, -1, sizeof(match));
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
    int d = dX.size(), p = pX.size();
    V = t*d+p;
    for (int i = 0; i < V; i++) {
        G[i].clear();
    }
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < p; j++) {
            if (dist[dX[i]][dY[i]][pX[j]][pY[j]] >= 0) {
                for (int k = dist[dX[i]][dY[i]][pX[j]][pY[j]]; k <= t; k++) {
                    add_edge((k-1)*d+i, t*d+j);
                    cout << "left " << (k-1)*d+i << " right " << t*d+j << endl;
                    
                }
            }
        }
    }
    cout << "-------" << endl;
    return bipartite_matching() == p;
}




void bfs(int x, int y, int d[MAX_X][MAX_Y]){
    queue<int> qx, qy;
    d[x][y] = 0;
    qx.push(x);
    qy.push(y);
    int depth = 0;
    int next = 0;
    while(!qx.empty()){
        int nx = qx.front();
        qx.pop();
        int ny = qy.front();
        qy.pop();
        for(int i = 0; i < 4; i++){
            int nextx = nx+dx[i], nexty = ny+dy[i];
            if (nextx >= 0 && nextx < X && nexty >= 0 && nexty < Y && field[nextx][nexty] == '.' && d[nextx][nexty] < 0){
                d[nextx][nexty] = d[nx][ny]+1;
                qx.push(nextx);
                qy.push(nexty);
            }
        }
    }
}


void solve(){
    int n = X*Y;
    dX.clear();
    dY.clear();
    pX.clear();
    pY.clear();
    memset(dist, -1, sizeof(dist));
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (field[x][y] == 'D') {
                dX.push_back(x);
                dY.push_back(y);
                bfs(x, y, dist[x][y]);
            }else if(field[x][y] == '.'){
                pX.push_back(x);
                pY.push_back(y);
            }
        }
    }
    int lb = -1, ub = n+1;
    while (ub-lb > 1) {
        int mid = (lb+ub)/2;
        cout << "----------"<<endl;
        cout << "mid " << mid << endl;
        if(C(mid))ub = mid;
        else lb = mid;
    }
    if(ub > n){
        cout << "impossible" << endl;
    }else{
        cout << ub << endl;
    }
}

int main(){
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d%d", &X, &Y);
        for (int j = 0; j < X; j++) {
            for (int k = 0; k < Y; k++) {
                cin >> field[j][k];
            }
        }
        solve();
    }
    return 0;
}
