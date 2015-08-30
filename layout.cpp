#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
#define N 1000
#define INF 1000001
struct edge {
    int from, cost;
};
vector<edge> g[N];
int d[N];

int main(){
    int n, ml, md;
    cin >> n >> ml >> md;
    int a, b, l;
    for (int i = 0; i < ml; i++) {
        scanf("%d%d%d", &a, &b, &l);
        a--;
        b--;
        edge e;
        e.from = a;
        e.cost = l;
        g[b].push_back(e);
    }
    for (int i = 0; i < md; i++) {
        scanf("%d%d%d", &a, &b, &l);
        a--;
        b--;
        edge e;
        e.from = b;
        e.cost = -l;
        g[a].push_back(e);
    }
    for (int i = 0; i < n-1; i++) {
        edge e;
        e.from = i+1;
        e.cost = 0;
        g[i].push_back(e);
    }
    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[0] = 0;
    for (int k = 0; k < n; k++) {
        bool update = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                edge e = g[i][j];
                if (d[e.from]+e.cost < d[i]) {
                    d[i] = d[e.from]+e.cost;
                }
            }
        }
        
    }
    if (d[n-1] == INF) {
        cout << -2 << endl;
    }else if(d[0] < 0){
        cout << -1 << endl;
    }else{
        cout << d[n-1] << endl;
    }
    return 0;
}