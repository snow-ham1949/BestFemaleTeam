ll inv[mxn];

void mod_inv() {
  inv[1] = 1;
  for (ll i = 2; i <= n; i++) {
    inv[i] = (p - p / i) * inv[p % i] % p;
  }
}
