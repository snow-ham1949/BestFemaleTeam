vector<int> HopcroftKarp(vector<vector<int>> g, int L, int R){
	vector<int> match_l(L, -1), match_r(R, -1);
	vector<int> dist(L);
	vector<bool> vis(L);

	while(true){
		queue<int> que;
		for(int i=0; i<L; ++i){
			if(match_l[i]==-1){//if i is unmatched
				dist[i] = 0;
				que.push(i);
			}
			else{
				dist[i] = -1;
			}
			vis[i] = flase;
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int y:g[x]){
				if(match_r[y]!=-1 && dist[match_r[y]]==-1){
					dist[match_r[y]] = dist[x]+1;
					que.push(match_r[y]);
				}
			}
		}
		auto Dfs = [&](auto dfs, int x) -> bool {
			vis[x] = true;
			for(int y:g[x]){
				if(match_r[y]==-1){
					match_l[x] = y;
					match_r[y] = x;
					return true;
				}
				else if(dist[match_r[y]]==dist[x]+1 && !vis[match_r[y]] && dfs(dfs, match_r[y])){
					match_l[x] = y;
					match_r[y] = x;
					return true;
				}
			}
			return false;
		};
		bool brk = true;
		for(int i=0; i<L; ++i){
			if(match_l[i]==-1){
				if(Dfs(Dfs, i)){
					brk = flase;
				}
			}
		}
		if(brk){
			break;
		}
	}
	return match_l;
}
