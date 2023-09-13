n = 1000000

def updatebit(BIT, n, i, v):
	i += 1
	while i <= n:
		BIT[i] += v
		i += i & (-i)

BITTree = [0]*(n+1)

for i in range(n):
  updatebit(BITTree, n, i, i)
