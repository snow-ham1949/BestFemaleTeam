// bridge is defined as an edge which, when removed, makes the graph disconnected (or more precisely, increases the number of connected components in the graph)
int low[N], dfn[N];
bool vis[N];
int e[M], x[M], y[M]; // e[i] = x[i] ^ y[i]
int stamp, bcc_no = 0;

vector<int> G[N], bcc[N]; // 1-base
stack<int> sta;
int bcc_id[M]; // edge i belongs to bcc_id[i], 1-base

void add_edge(int a, int b, int id){
  G[a].push_back(id);
  G[b].push_back(id);
  x[id] = a;
  y[id] = b;
  e[id] = a ^ b;
}

void dfs(int now, int par_eid) {
	vis[now] = true;
	dfn[now] = low[now] = (++stamp);
	for (int i : G[now]) {
		if (i == par_eid) continue;
		int to = (e[i] ^ now);
		if (!vis[to]) {
			sta.push(i); dfs(to, i);
			low[now] = min(low[now], low[to]);
			if (low[to] >= dfn[now]) {
				++bcc_no; int p; // p is edge index
				do {
					p = sta.top(); sta.pop();
          bcc_id[p] = bcc_no;
					bcc[bcc_no].push_back(p);
				} while (p != i);
			}
		}
		else if (dfn[to] < dfn[now]) {
			sta.push(i);
			low[now] = min(low[now], dfn[to]);
		}
	}
}

void bcc_solve(int n) {
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) dfs(i, -1);
}

// add_edge -> bcc_solve
// record nodes in bcc:
// for(int i = 1; i <= bcc_no; i++){
// 	for(auto eid:bcc[i]){
// 		bcc_node[i].insert(eS[eid].X);
// 		bcc_node[i].insert(eS[eid].Y);
// 	}
// }
//	pii eS[M]: edge i connect eS[i].X and eS[i].Y
// 	set<int> bcc_node[N]: bcc i has bcc_node[i] nodes
