struct disjoint_set{
	struct disjoint_set * parent;
	ll rank;
	ll data;

	void make_set(ll _data){
		data = _data;
		parent = this;
		rank = 0;
	}

	disjoint_set *find_set(){
		if(parent != this)
			parent = parent->find_set();
		return parent;
	}
 
};

void Union(disjoint_set *a, disjoint_set *b){
	disjoint_set *x = a->find_set(), *y = b->find_set();
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
