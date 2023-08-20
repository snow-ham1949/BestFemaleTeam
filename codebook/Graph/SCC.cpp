using Graph = vector<vector<int>>;
 
// Struct for finding strongly connected components in a graph
// Condensed graph is in reverse topological order
// "comp" gives component in condensed graph that node i is in
// Time Complexity: O(n + m)
struct SCC {
	Graph g;
	vector<int> comp;
	vector<int> ind;
	vector<int> sta;
	int di = 0; // DFS counter
	int cc = 0; // Comp count
 
	int dfs(int i) {
		if (ind[i] != -1) return (comp[i] == -1) ? ind[i] : di;
		ind[i] = di;
		int md = di;
		++di;
 
		sta.push_back(i);
		for (auto t : g[i]) md = min(md, dfs(t));
 
		if (md == ind[i]) {
			while(comp[i] == -1) {
				comp[sta.back()] = cc;
				sta.pop_back();
			}
			++cc;
		}
		return md;
	}
	SCC(const Graph& gr) : g(gr), comp(gr.size(), -1), ind(gr.size(), -1) {
		for (int i = 0; i < g.size(); ++i) dfs(i);
	}
};
