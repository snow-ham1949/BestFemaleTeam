const int N = 1e8 + 5;

bitset<N> num;
vector<int> prime;
void LS(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!num[i])
        prime.push_back(i);
    for (int j = 0; j < prime.size(); ++j) {
      if (i * prime[j] >= n) break;
      num[i * prime[j]] = 1;
      if (i % prime[j] == 0)break;
    }
  }
}
