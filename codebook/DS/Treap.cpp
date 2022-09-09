struct Node{
  // size: 以該節點為根的子樹大小
  // maxi:  以該節點為根的子樹的最大值
  // add: lazy add on this subtree
  // reverse: lazy reverse on this subtree
	int size,pri,val,add,maxi;
	bool reverse; 
	struct Node *l,*r;
};

Node *newnode(int val){
	Node *nnode = new Node;
	nnode->size = 1;
	nnode->val = val;
	nnode->maxi = val;
  nnode->add = 0;
	nnode->l = NULL;
	nnode->r = NULL;
	nnode->pri = rand()% 1000000;
	nnode->reverse = false;
	return nnode;	
}

int Size(Node *a){ 
	if(a == NULL) return 0;
	return a->size;
}

void updateadd(Node *a){
	if(a == NULL)	return;
	a->val += a->add;
	a->maxi += a->add;
	if(a->l != NULL)
		a->l->add += a->add;
	if(a->r != NULL)
		a->r->add += a->add;
	a->add = 0;
}

void updatemax(Node *a){
	if(a == NULL) 
		return;
	if(a->l == NULL && a->r == NULL)
	{
		a->maxi = a->val; return;
	}	
	if(a->l == NULL)
		a->maxi = max(a->val,a->r->maxi);
	else if (a->r == NULL)
		a->maxi = max(a->val,a->l->maxi);
	else
		a->maxi = max(a->val,max(a->l->maxi,a->r->maxi));			
}

void updatesize(Node *a){
	a->size = 1 + Size(a->l)+Size(a->r);
}

void updatereverse(Node *a){
	if(a == NULL)
		return;
	if(a->reverse == false)
		return;
	a->reverse = false;
	Node *tmp = a->r;
	a->r = a->l;
	a->l = tmp;
	if(a->r != NULL)
		a->r->reverse ^= true;
	if(a->l != NULL)
		a->l->reverse ^= true;
}

Node *merge(Node *a, Node *b){         // a 的個數 比 b 少 
	if(a == NULL)
		return b;
	if(b == NULL)
		return a;
	updateadd(a); 
  updateadd(b); 
  updatereverse(a);updatereverse(b);
	if(a->pri > b->pri)
	{
		a->r = merge(a->r,b);
		updatesize(a);
    updatemax(a); 
		return a;
	}
	else
	{
		b->l = merge(a,b->l);
		updatesize(b);
    updatemax(b);
		return b;
	}
} 

void split(Node *T, int k, Node **a, Node **b) // 把T用k分一半  放到a跟b那 
{       
	if(T == NULL)
	{
		*a = NULL; *b = NULL;
		return;
	}

	updateadd(T);
  updatereverse(T);
	if(Size(T->l) <= k-1)
	{
		*a = T;
		updateadd(*a);
    updatereverse(*a);
		split(T->r,k - Size(T->l) - 1,&((*a)->r),b);
		updatesize(*a); 
    updatemax(*a);
	}
	else
	{
		*b = T;
		updateadd(*b); 
    updatereverse(*b);
		split(T->l,k,a,&((*b)->l));
		updatesize(*b);	
    updatemax(*b);
	}
} 

// add val on [l..r]
void add(Node **T, int l, int r, int val)
{
	Node *left,*right;
	split(*T,l-1,&left,T);   // T: l~
	split(*T,r-l+1,T,&right);
	(*T)->add += val;
	*T = merge(merge(left,*T),right);
}

// reverse [l..r]
void reverse(Node **T, int l, int r)
{
	Node *left,*right;
	split(*T,l-1,&left,T);   // T: l~
	split(*T,r-l+1,T,&right);
	(*T)->reverse = true;
	*T = merge(merge(left,*T),right);
}

// find maxi in [l..r]
int rangemax(Node **T, int l, int r)
{
	int maxi;
	Node *left,*right;
	split(*T,l-1,&left,T);
	split(*T,r-l+1,T,&right);
	maxi = (*T)->maxi;
	*T = merge(merge(left,*T),right);
	return maxi;	
}

// insert 'val' at k_th position
void insert(Node **T, int k, int val){
	Node *a = newnode(val),*left,*right;
	split(*T,k,&left,&right); 
	a = merge(left,a); 	
	*T = merge(a,right);	
}

// delete k_th element
void del(Node **T, int k){
	Node *left, *right;
	split(*T,k-1,&left,T);
	split(*T,1,T,&right);
	Node *d = *T;
	free(d);
	*T = merge(left,right);	
}
 
// print inorder
// remember to update the root 
void print(Node *root){
	if(root == NULL) 
		return;  
  updatereverse(root);
  updateadd(root);
	print(root->l); 
	printf("%d ",root->val);
	print(root->r);    
}