#include<stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#define MAX_N 10001

using namespace std;
const int ST_SIZE = (1 << 15) -1;

double vx[ST_SIZE], vy[ST_SIZE];
double ang[ST_SIZE];
int s[MAX_N];
double prv[MAX_N];
int n;

void init(int i, int l, int r){
    ang[i] = 0.0;
    vx[i] = 0.0;
    if (r-l == 1) {
        vy[i] = s[l];
        return;
    }else{
        init(i*2+1, l, (r+l)/2);
        init(i*2+2, (r+l)/2, r);
        vy[i] = vy[i*2+1] + vy[i*2+2];
    }
}

void change(int i, double a, int k, int l, int r){
    printf("i:%d  a:%lf  k:%d  l:%d  r:%d\n", i, a, k, l, r);
    if (i <= l) {
        return;
    }else if(i < r){
        int chl = k*2+1;
        int chr = k*2+2;
        change(i, a, chl, l, (l+r)/2);
        change(i, a, chr, (l+r)/2, r);
        if (i <= (l+r)/2) {
            ang[k] += a;
            printf("k:%d  ang[k]:%lf\n", k, ang[k]);
        }
        
        double cosin = cos(ang[k]);
        double sine = sin(ang[k]);
        
        vx[k] = vx[chl] + cosin*vx[chr]-sine*vy[chr];
        vy[k] = vy[chl] + sine*vx[chr]+cosin*vy[chr];
    }
}

int main(){
    int c;
    while(scanf("%d %d", &n, &c) != EOF){
        for (int i = 0; i < n; i++) {
            scanf("%d", &s[i]);
            prv[i] = M_PI;
        }
        init(0, 0, n);
        for (int i = 0; i < n; i++) {
            printf("%lf %lf %lf\n", vx[i], vy[i], ang[i]);
        }
        int num;
        double a;
        for (int i = 0; i < c; i++) {
            scanf("%d %lf", &num, &a);
            double avg = a/180.0*M_PI;
            change(num, avg-prv[num],  0, 0, n);
            prv[num] = avg;
            printf("%.2f %.2f\n", vx[0], vy[0]);

        }
    }
    return 0;
}