n = 1000000

def updatebit(BITTree , n , i ,v):
	i += 1
	while i <= n:
		BITTree[i] += v
		i += i & (-i)

BITTree = [0]*(n+1)

for i in range(n):
  updatebit(BITTree, n, i, i)
