#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> iPair;
#define INF INT_MAX

void dijkstra(vector<iPair> *e, int src, int len, vector<ll> &dis){
    dis = vector<ll>(len+1 , INF);
    dis[src] = 0;
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    pq.push({0,src});
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(int i=0;i<e[u].size();i++){
            ll v = e[u][i].first;
            ll weight = e[u][i].second;
            if(dis[v]>dis[u]+weight){
                dis[v] = dis[u] + weight;
                pq.push({dis[v], v});
            }
        }
    }    
}

void print(vector<ll> &a, ll n){
    for(int i=0;i<n+1;i++){
        if(a[i]==INF){
            cout << -1 << " ";
        }else{
            cout << a[i] << " ";
        }
    }
    cout << "\n";
}

int main(){
    int n,m,p,q;
    ll t,T;
    cin >> n >> m >> p >> q >> t >> T;
    vector<iPair> e[n+1];
    vector<iPair> g[n+1];
    vector<ll> dis1;
    vector<ll> ans;
    for(int i=0;i<m;i++){
        int a,b,w;
        cin >> a >> b >> w;
        e[a].push_back({b,w});
        g[a].push_back({b,1});
    }
    for(int i=0;i<p;i++){
        int p1;
        cin >> p1;
        e[0].push_back({p1, 0});
    }
    dijkstra(e,0,n,dis1);
    vector<ll> dis2;
    for(int i=0;i<q;i++){
        int q1;
        cin >> q1;
        g[0].push_back({q1,0});
    }
    dijkstra(g,0,n,dis2);
    for(int i=0;i<dis2.size();i++){
        if(dis2[i]==INF){
            dis2[i] = -1;
        }
    }
    for(int i=0;i<dis2.size();i++){
        dis2[i] += t;
    }
    for(int i=1;i<dis1.size();i++){
        if(dis1[i] < dis2[i] && dis1[i] >= 0){
            ans.push_back(dis1[i]);
        }
    }
    int len = ans.size();
    cout << len;
}