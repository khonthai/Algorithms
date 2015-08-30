#include<stdio.h>
#include<vector>
using namespace std;
#define N 50
#define M 50
#define MAX_V 2602
#define INF 1e9
#define MAX_E 125100

struct edge{
    int to, cap, cost, rev;
};
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V];
int preve[MAX_E];
int v;

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
    v = 2+n+m+n*m;
    int s = n+m*n+m;
    int t = s+1;
    int a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a);
            for (int k = 0; k < n; k++) {
                add_edge(i, n+j*n+k, 1, a*(k+1));
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        add_edge(s, i, 1, 0);
    }
    for (int i = n; i < v-2; i++) {
        add_edge(i, t, 1, 0);
    }
    printf("%.2lf\n", (double)min_cost_flow(s, t, n)/n);
    return 0;
}