#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define SZ(a) (int)a.size()
#define endl '\n'
#define MAXN 50000000
#define X first
#define Y second

ll tree[MAXN+1];

ll lowbit(ll x){
  //cout << "working\n";
  return x & (-x);
}

void updateBIT(ll pos, ll value){
  for(ll i = pos; i <= MAXN; i += lowbit(i))
    tree[i] += value;
}

void solve() {
  for(ll i = 0; i < MAXN; i++){
    updateBIT(1, i);
    //cout << "update: " << tree[i] << "\n";
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
