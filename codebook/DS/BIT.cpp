// point update, range query
// range update, point query: 差分
// range update, range query: 要用兩個 BIT，一個維護差分D_i, 一個維護差分D_i * i

typedef struct Tree{
	ll *tree;
	ll size;
}BIT; 

ll lowbit(ll x){
	return x & (-x);
}

void init(BIT *ptr, ll size){
	ptr->size = size;
  ptr->tree = new ll[size+1]();
}

// add value on pos V
void updateBIT(BIT *ptr, ll pos, ll value){
	for(ll i = pos; i <= ptr->size; i += lowbit(i))
		ptr->tree[i] += value;
}

// build BIT tree V
BIT *build(int size, int data[]){
	BIT *newtree = new BIT;
	init(newtree,size);
	for(int i = 0; i < size; i++)
		updateBIT(newtree,i+1,data[i]);
	return newtree;
}

// get sum on [1 .. pos] V
ll getsum(BIT *ptr, ll pos){
	ll sum = 0;
	for(ll i = pos; i > 0; i -= lowbit(i))
		sum += ptr->tree[i];
	return sum;
}

// get sum on [l..r] V
ll rangesum(BIT *ptr, ll l, ll r){
	return getsum(ptr,r)-getsum(ptr,l-1);
}

// for range update and point query
// the array is preprocessed
void updaterange(BIT *ptr, int l, int r, int k){
    // Increase value at 'l' by 'k'
    updateBIT(ptr, l, k);
 
    // Decrease value at 'r+1' by 'k'
    updateBIT(ptr, r+1, -k);
}