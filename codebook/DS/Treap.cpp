int rnd() { return ((rand() % (1 << 15)) << 16) + (rand() % (1 << 15)); }

struct Treap{
  Treap *lc, *rc;
  int sz, pri, val;
  long long int sum;
  bool rev;
  Treap(int _val): lc(nullptr), rc(nullptr), sz(1), pri(rnd()), val(_val), sum(_val), rev(false){};
};
long long int SUM(Treap* a){
  return a? a->sum : 0;
}
int SZ(Treap *a){
  return a? a->sz:0;
}
void pull(Treap* a){
  if(!a){
    return;
  }
  a->sz = 1 + SZ(a->lc) + SZ(a->rc);
  a->sum = a->val + SUM(a->lc) + SUM(a->rc);
}
void push(Treap* a){
  if(a->rev){
    swap(a->lc, a->rc);
  }
  if(a && a->lc){
    a->lc->rev ^= a->rev;
  }
  if(a && a->rc){
    a->rc->rev ^= a->rev;
  }
  a->rev = 0;
}
Treap* merge(Treap* a, Treap* b){
  if(!a || !b)return a? a:b;
  push(a);
  push(b);
  if(a->pri > b->pri){
    a->rc = merge(a->rc, b);
    pull(a);
    return a;
  }
  else{
    b->lc = merge(a, b->lc);
    pull(b);
    return b;
  }
}
void split(Treap* t, int k, Treap* &a, Treap* &b){
  if(!t){
    a = b = nullptr;
    return;
  }
  push(t);
  if(SZ(t->lc)+1 <= k){
    a = t;
    split(t->rc, k-(SZ(t->lc)+1), a->rc, b);
    pull(a);
    return;
  }
  b = t;
  split(t->lc, k, a, b->lc);
  pull(b);
  return;
}
