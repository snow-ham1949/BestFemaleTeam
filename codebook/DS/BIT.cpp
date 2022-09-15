// point update, range query
// range update, point query: 差分
// range update, range query: 要用兩個 BIT，一個維護差分D_i, 一個維護差分D_i * i

// new instace: 
struct BIT{
	ll *tree;
	ll size;

	ll lowbit(ll x){
		return x & (-x);
	}

	void init(ll _size){
		size = _size;
		tree = new ll[size + 1]();		
	}

	// add value on pos
	void updateBIT(ll pos, ll value){
		for(ll i = pos; i <= size; i += lowbit(i))
			tree[i] += value;
	}

	void build_with_arr(ll _size, int data[]){
		init(_size);
		for(ll i = 0; i < size; i++){
			updateBIT(i+1, data[i]);
		}
	}

	// get sum on [1 .. pos]
	ll getsum(ll pos){
		ll sum = 0;
		for(ll i = pos; i > 0; i -= lowbit(i))
			sum += tree[i];
		return sum;
	}

	// get sum on [l..r]
	ll rangesum(ll l, ll r){
		return getsum(r)-getsum(l-1);
	}

	// for range update and point query
	// the array is preprocessed
	void updaterange(int l, int r, int k){
			// Increase value at 'l' by 'k'
			updateBIT(l, k);
	
			// Decrease value at 'r+1' by 'k'
			updateBIT(r+1, -k);
	}
}; 
