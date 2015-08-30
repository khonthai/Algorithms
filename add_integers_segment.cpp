#include<iostream>
#include<algorithm>
#define SIZE 200000
using namespace std;
int n, q;
int data[SIZE];
int datb[SIZE];


void add(int a, int b, int x, int k, int l, int r){
    
    if (b >= r && a <= l) {
        data[k] += x;
        return;
    }else if(b > l && a < r){
        datb[k]+= (min(b,r)-max(a,l))*x;
        int m = (l+r)/2;
        add(a, b, x, 2*k+1, l, m);
        add(a, b, x, 2*k+2, m, r);
    }
}

int sum(int a, int b, int k, int l, int r){
    if (a >= r || b <= l) {
        return 0;
    }
    if (b >= r && a <= l) {
        return data[k]*(r-l)+datb[k];
    }
    long long res = (min(b,r)-max(a,l))*data[k];
    int m = (l+r)/2;
    res += sum(a, b, 2*k+1, l, m);
    res += sum(a, b, 2*k+2, m, r);
    return res;
}



int main(){
    cin >> n >> q;
    int num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        add(i, i+1, num, 0, 0, n);
    }
    cout << endl;
    for (int i = 0; i < 3*n+1; i++) {
        cout << datb[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 3*n+1; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
    char c;
    int x, y, z;
    for (int i = 0; i < q; i++) {
        cin >> c;
        if (c == 'C') {
            cin >> x >> y >> z;
            add(x-1, y, z, 0, 0, n);
        }else{
            cin >> x >> y;
            cout << sum(x-1, y, 0, 0, n)<<endl;
        }
    }
    return 0;
}