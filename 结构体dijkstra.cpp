struct Edge {
    int from, to;
    LL dist;
    Edge(int u, int v, LL w) : from(u), to(v), dist(w){}
};

struct cmp
{
    bool operator() (const PII &x, const PII &y) {
        return y.second < x.second;
    }
};

struct Dijkstra
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    LL d[maxn];

    void init(int n)
    {
        this->n = n;
        for (int i = 0; i <= n; ++i) G[i].clear();
        edges.clear();
    }

    void addedge(int u, int v, int w)
    {
        edges.push_back(Edge(u, v, w));
        int m = edges.size();
        G[u].push_back(m - 1);
    }

    LL dijkstra(int s, int t, LL *d)
    {
        priority_queue<PII, vector<PII>, cmp> q;
        for (int i = 0; i <= n; ++i) d[i] = INF;
        d[s] = 0;
        memset(vis, 0, sizeof(vis));
        q.push(mp(s, 0));
        while (!q.empty())
        {
            PII t = q.top(); q.pop();
            int u = t.first;
            if (vis[u]) continue;
            vis[u] = true;
            int _s = G[u].size();
            for (int i = 0; i < _s; ++i)
            {
                Edge &e = edges[G[u][i]];
                if (d[e.to] > d[u] + e.dist)
                {
                    d[e.to] = d[u] + e.dist;
                    q.push(mp(e.to, d[e.to]));
                }
            }
        }
        return d[t];
    }
};