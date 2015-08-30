#include<stdio.h>
#include<vector>
using namespace std;
#define INF 1e9
#define MAX_V 1000
#define MAX_E 10000
struct edge{
    int to, cap, cost, rev;
};
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V];
int preve[MAX_E];
int v, e;

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
    scanf("%d %d", &v, &e);
    int a, b, c;
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a-1, b-1, 1, c);
    }
    printf("%d\n", min_cost_flow(0, v-1, 2));
    return 0;
}



