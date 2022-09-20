vector<pair<int, int>> g[kN];
vector<int> euler_tour;
vector<bool> visited(kN, false);
void EulerTour(int x){
	while(!g[x].empty()){
		auto [u, e] = g[x].back();//e is the ID of the edge
		g[x].pop_back();
		if(!visited[e]){
			visited[e] = true;
			EulerTour(u);
			euler_tour.push_back(e);
		}
	}
}
