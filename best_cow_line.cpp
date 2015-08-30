#include<iostream>
using namespace std;
#define MAX 2000
int main(){
    int n;
    cin >> n;
    char s[MAX+1], t[MAX+1];
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int a = 0, b = n-1, j = 0;
    while ( a <= b) {
        if (s[a] < s[b]) {
            t[j] = s[a++];
        }else if(s[a] > s[b]){
            t[j] = s[b--];
        }else{
            int k = a;
            int l = b;
            k++;
            l--;
            bool left = true;
            while (k <= l) {
                if (s[k] < s[l]) {
                    break;
                }else if(s[k] > s[l]){
                    left = false;
                    break;
                }else{
                    k++;
                    l--;
                }
            }
            if (left) {
                t[j] = s[a++];
            }else{
                t[j] = s[b--];
            }
        }
        j++;
    }
    for (int i = 0; i < n; i++) {
        if (i > 0 && i%80 == 0) {
            cout << endl;
        }
        cout << t[i];
    }
    return 0;
}