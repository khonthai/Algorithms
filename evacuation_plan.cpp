#include<stdio.h>
#include<vector>
#include<math.h>
using namespace std;
#define MAX_N 100
#define MAX_M 100
#define MAX_V 202
#define INF 1e9
#define MAX_E 10200
struct edge{
    int to, cap, cost, rev;
};
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V];
int preve[MAX_E];
int v;

int X[MAX_N], Y[MAX_N], B[MAX_N];
int P[MAX_M], Q[MAX_M], C[MAX_M];
int E[MAX_N][MAX_M];

void add_edge(int from, int to, int cap, int cost){
    G[from].push_back((edge) {to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size()-1});
}

int min_cost_flow(int s, int t, int f){
    int res = 0;
    while (f > 0) {
        bool update = true;
        fill(dist, dist+v, INF);
        dist[s] = 0;
        while (update == true) {
            update = false;
            for (int i = 0 ; i < v; i++) {
                for (int j = 0; j < G[i].size(); j++) {
                    edge &ed = G[i][j];
                    if (ed.cap > 0 && dist[i]+ed.cost < dist[ed.to]) {
                        dist[ed.to] = dist[i]+ed.cost;
                        prevv[ed.to] = i;
                        preve[ed.to] = j;
                        update = true;
                    }
                }
            }
        }
        if (dist[t] == INF) {
            return -1;
        }
        int d = f;
        for (int i = t; i != s; i = prevv[i]) {
            d = min(d, G[prevv[i]][preve[i]].cap);
        }
        f -= d;
        res += d*dist[t];
        for (int i = t; i != s; i = prevv[i]) {
            edge &ed = G[prevv[i]][preve[i]];
            ed.cap -= d;
            G[i][ed.rev].cap += d;
        }
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    v = n+m+2;
    int f = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &X[i], &Y[i], &B[i]);
        add_edge(0, i+1, B[i], 0);
        f += B[i];
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &P[i], &Q[i], &C[i]);
        add_edge(n+1+i, n+m+1, C[i], 0);
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int c = sqrt((P[j]-X[i])*(P[j]-X[i])+(Q[j]-Y[i])*(Q[j]-Y[i]));
            add_edge(i+1, n+1+j,INF, c);
            scanf("%d", &E[i][j]);
            sum += E[i][j]*c;
        }
    }
    int lowest = min_cost_flow(0, n+m+1, f);
    if (sum == f) {
        printf("OPTIMAL\n");
    }else{
        printf("SUBOPTIMAL\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d%c", G[n+1+j][i+1].cap, j+1 == m? '\n' : ' ');
            }
        }
    }
    return 0;
}