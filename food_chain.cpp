#include<iostream>
#include<vector>
using namespace std;
#define MAX_K 100000


vector<int> p, rank2, number;


void makeSet(int i){
    p[i] = i;
    rank2[i] = 0;
    number[i] = 1;
}
int find(int i){
    if (i != p[i]) {
        p[i] = find(p[i]);
    }
    return p[i];
}
void link(int x, int y){
    if (x != y) {
        if (rank2[x] < rank2[y]) {
            p[x] = y;
            number[y] += number[x];
        }else{
            p[y] = x;
            number[x] += number[y];
            if (rank2[x] == rank2[y]) {
                rank2[x]++;
            }
        }
    }
}
void unionn(int x, int y){
    link(find(x), find(y));
}

bool same(int x, int y){
    return find(x) == find(y);
}
void init(int size){
    rank2.resize(size, 0);
    p.resize(size, 0);
    number.resize(size, 0);
    for (int i = 0; i < size; i++) {
        makeSet(i);
    }
}

int t[MAX_K], a[MAX_K], b[MAX_K];

int main(){
    int N,K;
    cin >> N >> K;
    
    for (int i = 0; i < K; i++) {
        cin >> t[i] >> a[i] >> b[i];
    }
    init(3*N);
    int ans = 0;
    for (int i = 0; i < K; i++) {
        int x = a[i] -1;
        int y = b[i] -1;
        if (x >=N || y >= N) {
            ans++;
        }else{
            if (t[i] == 1) {
                if (same(x, y+N) || same(x, y+2*N)) {
                    ans++;
                }else{
                    unionn(x,y);
                    unionn(x+N, y+N);
                    unionn(x+2*N, y+2*N);
                }
            }else{
                if (same(x, y) || same(x, y+2*N)) {
                    ans++;
                }else{
                    unionn(x, y+N);
                    unionn(x+N, y+2*N);
                    unionn(x+2*N, y);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}

