const int mxn = 20000 + 5;
int miu[mxn],  vis[mxn];
vector<int> prime;

void init() {
#define eb emplace_back
  miu[1] = 1;
  for (int i = 2; i < mxn; i++) {
    if (!vis[i]) {
      prime.eb(i);
      miu[i] = -1;
    }
    for (int j = 0; j < SZ(prime) && i * prime[j] < mxn; j++) {
      vis[i * prime[j]] = 1;
      if (i % prime[j]) miu[i * prime[j]] = -miu[i];
      else miu[i * prime[j]] = 0;
    }
  }
}