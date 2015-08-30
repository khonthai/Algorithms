#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>
#include<vector>
using namespace std;
#define MAX_N 10000
//int a[MAX_N+1], b[MAX_N+1];
vector<pair<int,int> > v;

bool pairCompare(const pair<int,int>& one, const pair<int,int>& two){
    return one.first < two.first;
}


int main(){
    int N, L, P;
    cin >> N;
    int a, b;
    for (int i = 0; i < N ; i++) {
        cin >> a >> b;
        v.push_back(make_pair(a,b));
    }
    cin >> L >> P;
    for (int i = 0; i < N; i++) {
        v[i].first = L-v[i].first;
    }
    v.push_back(make_pair(L,0));
    sort(v.begin(), v.end(), pairCompare);
    priority_queue<int> q;
    bool f = true;
    int ans = 0;
    for ( int i = 0; i <= N; i++) {
        while (P < v[i].first && !q.empty()) {
            P += q.top();
            q.pop();
            ans++;
        }
        if (P < v[i].first) {
            f = false;
            break;
        }else{
            q.push(v[i].second);
        }
    }
    if (f) {
        cout << ans << endl;
    }else{
        cout << -1 << endl;
    }
    return 0;
}