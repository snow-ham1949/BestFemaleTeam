struct SW_Min_Cut {  
    static const int maxn = 500 + 5;
    int edge[maxn][maxn];
    int n;
    int vis[maxn], del[maxn], weight[maxn];

    void Init(int _n)
    {   
        memset(edge, 0, sizeof(edge));
        memset(del, 0, sizeof(del));
        n = _n;
    }
    
    void AddEdge(int u, int v, int w)
    {   
        edge[u][v] += w;
        edge[v][u] += w;
    }

    void Search(int &s, int &t)
    {   
        memset(vis, 0, sizeof(vis));
        memset(weight, 0, sizeof(weight));
        s = t = -1;
        while (true)
        {   
            int mx = -1, cur = 0;
            for (int i = 0; i < n; i++)
            {   
                if (!del[i] && !vis[i] and mx < weight[i])
                {   
                    cur = i, mx = weight[i];
                }
            }
            if (mx == -1) break;
            vis[cur] = 1;
            s = t, t = cur;
            for (int i = 0; i < n; i++)
            {   
                if (!vis[i] && !del[i]) weight[i] += edge[cur][i];
            }
        }
    }

    int Solve()
    {   
        int res = INT_MAX;
        for (int i = 0, x, y; i < n - 1; i++)
        {   
            Search(x, y);
            res = min(res, weight[y]);
            del[y] = 1;
            for (int j = 0; j < n; j++)
            {   
                edge[x][j] = (edge[j][x] += edge[y][j]);
            }
        }
        return res;
    }
} graph;