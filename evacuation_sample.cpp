#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#define MAX_X 15
#define MAX_Y 15
#define MAX_V 15*15*100
using namespace std;


struct P { int x, y; };

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int X, Y;
char field[MAX_X][MAX_Y];

int dist[MAX_X][MAX_Y][MAX_X][MAX_Y];
vector<P> ds, ps;

vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int u, int v){
  G[u].push_back(v);
  G[v].push_back(u);
}

bool dfs(int v){
  used[v] = true;
  for(int i = 0; i < G[v].size(); i++){
    int u = G[v][i];
    int u_pair = match[u];
    if(u_pair < 0 || (!used[u_pair] && dfs(u_pair))){
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

void bfs(P door, int d[MAX_X][MAX_Y]){
  queue<P> q;
  d[door.x][door.y] = 0;
  q.push(door);
  while(!q.empty()){
    P p = q.front(); q.pop();
    for(int i = 0; i < 4; i++){
      int nx = p.x + dx[i], ny = p.y + dy[i];
      if(field[nx][ny] == '.' && d[nx][ny] < 0){
        d[nx][ny] = d[p.x][p.y] + 1;
        q.push((P){nx, ny});
      }
    }
  }
}

void solve(){
  int max_t = X * Y;
  ds.clear(); ps.clear();
  memset(dist, -1, sizeof(dist));
  for(int i = 0; i < MAX_V; i++){
    G[i].clear();
  }

  for(int x = 0; x < MAX_X; x++){
    for(int y = 0; y < MAX_Y; y++){
      if(field[x][y] == 'D'){
        ds.push_back((P){x, y});
        bfs((P){x, y}, dist[x][y]);
      }else if(field[x][y] == '.'){
        ps.push_back((P){x, y});
      }
    }
  }

  for(int i = 0; i < ds.size(); i++){
    for(int j = 0; j < ps.size(); j++){
      P d = ds[i], p = ps[j];
      if(dist[d.x][d.y][p.x][p.y] >= 0){
        for(int t = dist[d.x][d.y][p.x][p.y]; t <= max_t; t++){
          add_edge((t - 1) * ds.size() + i, max_t * ds.size() + j);
            cout << "max_t " << max_t << endl;
            if (max_t == 12) {
                cout << "left " << (t-1)*ds.size()+i << " right " << max_t * ds.size() + j<< endl;
            }
        }
      }
    }
  }

  if(ps.size() == 0){
    printf("0\n");
    return;
  }

  int num = 0;
  memset(match, -1, sizeof(match));
  for(int v = 0; v < max_t * ds.size(); v++){
    memset(used, 0, sizeof(used));
    if(dfs(v)){
      if(++num == ps.size()){
        printf("%lu\n", (v / ds.size() + 1));
        return;
      }
    }
  }
  printf("impossible\n");
}

int main(){
  int C;
  scanf("%d", &C);

  while(C--){
    scanf("%d %d", &X, &Y);
    memset(field, 'X', sizeof(field));
    for(int i = 1; i <= X; i++){
      scanf("%s", &field[i][1]);
    }
    solve();
  }
}
