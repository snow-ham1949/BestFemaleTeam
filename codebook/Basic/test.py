n = 1000000

def updatebit(BITTree , n , i ,v):

	# index in BITree[] is 1 more than the index in arr[]
	i += 1

	# Traverse all ancestors and add 'val'
	while i <= n:

		# Add 'val' to current node of BI Tree
		BITTree[i] += v

		# Update index to that of parent in update View
		i += i & (-i)


# Create and initialize BITree[] as 0
BITTree = [0]*(n+1)

# Store the actual values in BITree[] using update()
for i in range(n):
  updatebit(BITTree, n, i, i)
