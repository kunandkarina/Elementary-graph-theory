#include<iostream>
#include<vector>
using namespace std;
#define Maxn 300005
#define level 19
vector<int> depth(Maxn);
vector<vector<int>> parent(Maxn, vector<int>(level,-1));

void dfs(int root, int prev, vector<int> *t){
    depth[root] = depth[prev] + 1;
    parent[root][0] = prev;
    for(int i=0;i<t[root].size();i++){
        if(t[root][i] != prev){
            dfs(t[root][i], root, t);
        }
    }
}

void computeAncestor(int n){
    for(int i=1;i<level;i++){
        for(int node=1;node<=n;node++){
            if(parent[node][i-1] != -1){
                parent[node][i] = parent[parent[node][i-1]][i-1];
            }
        }
    }
}

int LCA(int u, int v){
    if(depth[u] > depth[v]){
        swap(u,v);
    }

    int diff = depth[v] - depth[u];
    for(int i=0;i<level;i++){
        if((diff >> i) & 1){
            v = parent[v][i];
        }
    }

    if(u==v){
        return depth[u];
    }
    for(int i=level-1;i>=0;i--){
        if(parent[u][i] != parent[v][i]){
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return depth[parent[u][0]];
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int n; cin >> n;
    vector<int> t[n+1];
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        t[x].push_back(y);
        t[y].push_back(x);
    }
    dfs(1,0,t);
    computeAncestor(n);
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++){
        int u, v;
        cin >> u >> v;
        cout << depth[u] + depth[v] - 2*LCA(u, v) << "\n";
    }
}


