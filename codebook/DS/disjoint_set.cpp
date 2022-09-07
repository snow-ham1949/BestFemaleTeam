struct disjoint_set{
	struct disjoint_set * parent;
	ll rank;
	ll data;
};

disjoint_set *make_set(ll data){
	disjoint_set *newset  = new disjoint_set;
	newset->data = data;
	newset->parent = newset;
	newset->rank = 0;
  return newset;
}

disjoint_set *find_set(disjoint_set *x){
	if(x->parent != x)
		x->parent = find_set(x->parent);
	return x->parent;
}

void Union(disjoint_set *a, disjoint_set *b){
	disjoint_set *x = find_set(a), *y = find_set(b);
	if(x == y)
		return;
	if(x->rank > y->rank)
		y->parent = x;
	else if (x->rank == y->rank)
	{
		y->parent = x;
		x->rank ++;
	}
	else
		x->parent = y;
  return;
} 
