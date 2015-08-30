#include<math.h>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define EPS 0.0001
int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    double l[n];
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        scanf("%lf",&l[i]);
        sum += l[i];
    }
    double s = 0.0;
    double t = sum/k;
    double m;
    for (int j = 0; j < 100; j++) {
        m = (t+s)/2;
        int num = 0;
        for (int i = 0; i < n; i++) {
            num += (int)(l[i]/m);
        }
        if(num < k){
            t = m;
        }else{
            s = m;
        }
    }
    printf("%.2f\n", floor(m*100)/100);
    return 0;
}