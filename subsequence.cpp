#include<stdio.h>
#include<algorithm>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int n, s;
        scanf("%d%d", &n, &s);
        int a[n];
        for (int j = 0; j < n; j++) {
            scanf("%d",&a[j]);
        }
        int head = 0;
        int sum = 0;
        int ans = n+1;
        int j = 0;
//        for (;;) {
//            while (j < n&& sum < s) {
//                sum += a[j++];
//            }
//            if (sum < s) {
//                break;
//            }
//            ans = min(ans, j-head);
//            sum -= a[head++];
//        }
        for (j = 0;j < n;j++) {
            sum+=a[j];
            if (sum < s) {
                
            }else if(sum == s){
                ans = min(ans, j-head+1);
            }else {
                while (sum - a[head] > s) {
                    sum -= a[head];
                    head++;
                }
                ans = min(ans, j-head+1);
            }
            
        }
        
        if (ans > n) {
            ans = 0;
        }
        printf("%d\n",ans);
    }
    return 0;
}