typedef unsigned long long ull;

const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

const int N = 1e6 + 10;

ull hash[N];
std::vector<int> edge[N];

void dfs(int x, int p) {
  hash[x] = 1;
  for (int i : edge[x]) {
    if (i == p) {
      continue;
    }
    getHash(i, x);
    hash[x] += shift(hash[i]);
  }
}

// usage:
// dfs(1, 0)
