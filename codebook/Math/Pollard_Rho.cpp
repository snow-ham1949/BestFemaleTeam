long long int mult(long long int a, long long int b, long long int m){
	return (a*b)%m;
}
long long int f(long long int x, long long int m){//fake random function
	return (mult(x, x, m)+1)%m;
}
long long int pollard_rho(long long int n){
	if(n%2==0){
		return 2;
	}
	long long int xi = 2, xj = 2;
	int i = 1, j = 1;
	while(true){
		j++;
		xj = f(xj, n);
		int d = __gcd(abs(xi-xj), n);
		if(d!=1){
			return d;
		}
		if(j==i*2){
			i*=2;
			xi = xj;
		}
	}
}
