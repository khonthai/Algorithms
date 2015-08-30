#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;
#define MAX_N 100
#define MAX_F 100
#define MAX_D 100
#define INF 1e9
#define MAX_V 405
#define MAX_E 100000

struct edge{
    int to;
    int cap;
    int rev;
};

vector<edge> G[MAX_N*2+MAX_F+MAX_D+2];
bool used[MAX_V];

void add_edge(int from, int to, int cap){
    G[from].push_back((edge){to, cap, G[to].size()});
    G[to].push_back((edge){from, 0, G[from].size()-1});
}

int dfs(int v, int t, int f){
    if (v == t) {
        return f;
    }
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t){
    int flow = 0;
    for (; ; ) {
        memset(used, 0, sizeof(used));
        int f = dfs(s,t, INF);
        if (f == 0) {
            return flow;
        }
        flow+=f;
    }
}

int main(){
    int n, f, d;
    scanf("%d %d %d", &n, &f, &d);
    for (int i = 1; i <= f; i++) {
        add_edge(0, i, 1);
    }
    for (int i = f+n*2+1; i <= f+n*2+d; i++) {
        add_edge(i, f+n*2+d+1, 1);
    }
    for (int i = f+1; i <=f+n; i++) {
        add_edge(i, i+n, 1);
    }
    int fi, di;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &fi, &di);
        int a;
        for (int j = 0; j < fi; j++) {
            scanf("%d", &a);
            add_edge(a, f+i, 1);
        }
        
        for (int j = 0; j < di; j++) {
            scanf("%d", &a);
            add_edge(f+n+i, f+n*2+a, 1);
        }
    }
    int ans = max_flow(0, f+n*2+d+1);
    printf("%d\n", ans);
    return 0;
}