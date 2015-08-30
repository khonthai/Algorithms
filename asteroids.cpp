#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define MAX_N 500

int n, k;

vector<int> G[MAX_N*2];
int match[MAX_N*2];
bool used[MAX_N*2];

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
    for (int i = 0; i < n*2; i++) {
        if (match[i] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(i)) {
                res++;
            }
        }
    }
    return res;
}

int main (){
    while(scanf("%d%d", &n, &k) != EOF) {
        int r, c;
        for (int i = 0; i < k; i++) {
            scanf("%d%d", &r, &c);
            add_edge(r-1, n+c-1);
        }
        memset(match, -1, sizeof(match));
        printf("%d\n", bipartite_matching());
    }
    return 0;
}