// using default code of Geometry
// including +, -, *, ori, cross, sign, eps
void convex_hull(vector<pll> &dots) { // n=1 => ans = {}
  // sort by x, then y
  sort(dots.begin(), dots.end());
  // start from left
  vector<pll> ans(1, dots[0]);
  // ct=0: lower part, ct=1: upper part
  for (int ct = 0; ct < 2; ++ct, reverse(dots.begin(), dots.end()))
    for (int i = 1, t = SZ(ans); i < SZ(dots); ans.push_back(dots[i++]))
      // if cross < 0: pop out element (==0? 看共線怎麼算)
      while (SZ(ans) > t && ori(ans[SZ(ans) - 2], ans.back(), dots[i]) <= 0)
        ans.pop_back();
  // pop the start point(only count once)
  ans.pop_back(), ans.swap(dots);
}
