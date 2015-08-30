#include<iostream>
#include<queue>
using namespace std;
priority_queue<int> L;
long long ans = 0;

void rec(){
    if (L.size() <= 1) {
        return;
    }
    int a = L.top();
    L.pop();
    int b = L.top();
    L.pop();
    ans += -(a+b);
    L.push(a+b);
    rec();
}


int main(){
    int n;
    cin >> n;
    
    int a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        L.push(a*(-1));
    }
    rec();
    cout << ans << endl;
    return 0;
}