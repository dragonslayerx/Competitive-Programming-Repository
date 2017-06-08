
#define NN 1505
 
int cap[NN][NN];
vector<vector<int> > adj;

int q[NN], prev[NN];
int dinic( int n, int s, int t )
{
    int flow = 0;
    while( true )
    {
        // find an augmenting path
        memset( prev, -1, sizeof(prev) );
        int qf = 0, qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], i = 0, v; i < adj[u].size(); i++ )
                if( prev[v = adj[u][i]] == -1 && cap[u][v] )
                    prev[q[qb++] = v] = u;
 
        // see if we're done
        if( prev[t] == -1 ) break;
 
        // try finding more paths
        for( int z = 0; z < n; z++ ) if( cap[z][t] && prev[z] != -1 )
        {
            int bot = cap[z][t];
            for( int v = z, u = prev[v]; u >= 0; v = u, u = prev[v] )
                bot = min(bot, cap[u][v]);
            if( !bot ) continue;
 
            cap[z][t] -= bot;
            cap[t][z] += bot;
            for( int v = z, u = prev[v]; u >= 0; v = u, u = prev[v] )
            {
                cap[u][v] -= bot;
                cap[v][u] += bot;
            }
            flow += bot;
        }
    }
    return flow;
}
