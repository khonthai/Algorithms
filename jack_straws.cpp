#include<stdio.h>
using namespace std;
#define MAX_N 13
int n;
vector<int> G[MAX_N];

double add(double a, double b){
    if (abs(a+b) < EPS * (abs(a) + abs(b))) {
        return 0;
    }
    return a + b;
}


struct P{
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y){
    }
    P operator + (P p){
        return P(add(x, p.x), add(y, p.y));
    }
    P operator - (P p){
        return P(add(x, -p.x), add(y, -p.y));
    }
    P operator * (double d){
        return P(x*d, y*d);
    }
    double dot(P p){
        return add(x*p.x, y*p.y);
    }
    double det(P p){
        return add(x*p.y, -y*p.x);
    }
};


bool on_seg(P p1, P p2, P q1, P q2){
    
}

bool isCrossDirectly(P p1, P p2, P q1, P q2){
    
}

int main(){
    scanf("%d", &n);
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    }
    int a = 1, b = 1;
    while (a != 0 && b != 0) {
        scanf("%d %d", &a, &b);
        
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            
            isCrossDirectly(
        }
    }
	return 0;
}
