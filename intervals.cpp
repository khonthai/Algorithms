#include<iostream>
#include<utility>
#include<vector>
using namespace std;
#define MAX_V 200
#define INF 1e9
#define MAX_E 1000
int N, k, v;
struct edge{
    int to, cap, cost, rev;
};
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V];
int preve[MAX_E];
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
    scanf("%d %d", &N, &k);
    int a[MAX_V], b[MAX_V], w[MAX_V];
    vector<int> x;
    int s, t;
    
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &a[i], &b[i], &w[i]);
        x.push_back(a[i]);
        x.push_back(b[i]);
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    int m = x.size();
    s = m;
    t = s+1;
    v = t + 1;
    
    for(int i = 0; i < v; i++){
        G[i].clear();
    }
    int res = 0;
    add_edge(s, 0, k, 0);
    add_edge(m-1, t, k, 0);
    for (int i = 0; i < m-1; i++) {
        add_edge(i, i+1, INF, 0);
    }

    for (int i = 0; i < N; i++) {
        int u = find(x.begin(), x.end(), a[i]) - x.begin();
        int y = find(x.begin(), x.end(), b[i]) - x.begin();
        add_edge(y, u, 1, w[i]);
        add_edge(s, y, 1, 0);
        add_edge(u, t, 1, 0);
        res -= w[i];
    }
    
    res += min_cost_flow(s, t, k+N);
    printf("%d\n", -res);
    return 0;
}