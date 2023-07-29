#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define SZ(a) (int)a.size()
#define X first
#define Y second

const int N = 1e7;
ll bit[N + 1];

void upd(ll pos, ll value){
  for(ll i = pos; i <= N; i += i & -i)
    bit[i] += value;
}

void solve() {
  for(ll i = 0; i < N; i++){
    upd(1, i);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
