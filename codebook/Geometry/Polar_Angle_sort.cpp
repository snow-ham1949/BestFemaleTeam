// using geometry default code
// sign, cross
bool cmp(pdd a, pdd b) {
  #define is_neg(k) (sign(k.Y) < 0 || (sign(k.Y) == 0 && sign(k.X) < 0))
  // 從180度開始逆時針
  int A = is_neg(a), B = is_neg(b);
  // 在上面的排後面
  if (A != B)
    return A < B;
  // 角度相同, 比到原點的距離
  if (sign(cross(a, b)) == 0)
    return abs2(a) < abs2(b);
  return sign(cross(a, b)) > 0;
}