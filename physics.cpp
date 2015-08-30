#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#define N 100
#define g 10.0
using namespace std;
int n, h, r, t;
double y[N];

double cal(int t){
    if (t < 0) {
        return h;
    }
    double T = sqrt(2*h/g);
    int k = (int)(t/T);
    if (k % 2 == 0) {
        double d = t-k*T;
        return h-g*d*d/2;
    }else{
        double d = (k+1)*T-t;
        return h-g*d*d/2;
    }
}

int main(){
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> n >> h >> r >> t;
        for (int j = 0; j < n; j++) {
            y[j] = cal(t-j);
        }
        sort(y, y+n);
        for (int j = 0; j < n; j++) {
            printf("%.2f%c", y[j]+2*r*j/100.0, j+1 == n ? '\n' : ' ');
        }
        
    }
    return 0;
}