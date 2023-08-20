using Graph = vector<vector<int>>;

// using SCC
// addClause(i, twosat.neg(j)) adds clause i, -j
// solve() returns empty vector if unsolvable
// Time Complexity: O(n + m)
struct TwoSat {
	const int n;
	Graph g; // Implication graph, of size 2*n

	TwoSat(int nodes) : n(nodes), g(2*nodes) {}

	int neg(int i) {
		return i >= n ? i-n : i+n;
	}
	void addClause(int a, int b) {
		g[neg(a)].push_back(b);
		g[neg(b)].push_back(a);
	}
	vector<bool> solve() {
		SCC scc(g);

		vector<int> inv(scc.cc);
		for (int i = 0; i < 2*n; ++i) {
			inv[scc.comp[i]] = scc.comp[neg(i)];
		}

		vector<int> state(scc.cc, -1);
		for (int i = 0; i < scc.cc; ++i) {
			if (state[i] != -1) continue;
			if (i == inv[i]) return {};
			state[i] = 1;
			state[inv[i]] = 0;
		}

		vector<bool> res(n);
		for (int i = 0; i < n; ++i) res[i] = state[scc.comp[i]];
		return res;
	}
};
