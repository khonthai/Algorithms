#include <iostream>
#include <complex>
#include <sstream>
#include <string>
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <vector>
#include <set>
#include <limits>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
#define REP(i, j) for(int i = 0; i < (int)(j); ++i)
#define FOR(i, j, k) for(int i = (int)(j); i < (int)(k); ++i)
#define P pair<int, int>
#define SORT(v) sort((v).begin(), (v).end())
#define REVERSE(v) reverse((v).begin(), (v).end())
//#define int long long
const int MAX_N = 1e5 + 10;
const int MAX_ST = (1 << 18) - 1;

int N, M, A[MAX_N], sorted_A[MAX_N];
vector<int> seg[MAX_ST];

void init(int k, int l, int r){
  if(r - l <= 1) seg[k].push_back(A[l]);
  else{
    int chl = k * 2 + 1, chr = k * 2 + 2;
    init(chl, l, (l + r) / 2);
    init(chr, (l + r) / 2, r);
    seg[k].resize(r - l);
    merge(seg[chl].begin(), seg[chl].end(), seg[chr].begin(), seg[chr].end(), seg[k].begin());
  }
}

int cnt(int a, int b, int x, int k, int l, int r){
  if(r <= a || l >= b) return 0;
  else if(l >= a && r <= b) return upper_bound(seg[k].begin(), seg[k].end(), x) - seg[k].begin();
  return cnt(a, b, x, k * 2 + 1, l, (l + r) / 2) + cnt(a, b, x, k * 2 + 2, (l + r) / 2, r);
}

int main() {
  scanf("%d %d", &N, &M);
  REP(i, N){
    scanf("%d", &A[i]);
    sorted_A[i] = A[i];
  }
  sort(sorted_A, sorted_A + N);
  init(0, 0, N);
  REP(z, M){
    int l, r, k; scanf("%d %d %d", &l, &r, &k);
    --l;
    int hi = N - 1, lo = -1;
    while(hi - lo > 1){
      int m = (hi + lo) / 2, x = sorted_A[m];
      int c = cnt(l, r, x, 0, 0, N);
      //debug
      cout <<lo <<", " <<m <<", " <<hi <<" | " <<x <<", " <<c <<endl;
      if(c >= k) hi = m;
      else lo = m;
    }
    printf("%d\n", sorted_A[hi]);
  }
  return 0;
}
