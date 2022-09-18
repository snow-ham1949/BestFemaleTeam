int ifloor(int a,int b)
// if a/b < 0 && a%b!=0
// minus 1
{ return a / b - (a % b && a < 0 ^ b < 0); }
int iceil(int a,int b)
// if a/b > 0 && a%b!=0
// plus 1
{ return a / b + (a % b && a < 0 ^ b > 0); }
