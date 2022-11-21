#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef pair<ll, ll> iPair;
#define Maxn 200005
#define INF LLONG_MAX / 10

void dijkstra(vector<iPair> *e, int src, int len, vector<ll> &dis){      //初始化地方有bug
    dis = vector<ll>(len, INF);
    dis[src] = 0;
    // 按照dis距離由小到大排列
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    pq.push({0,src});
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(int i=0;i<e[u].size();i++){
            ll v = e[u][i].first;
            ll weight = e[u][i].second;
            if(dis[v] > dis[u] + weight){
                dis[v] = dis[u] + weight;
                pq.push({dis[v], v});
            }
        }
    }
}
void initial(vector<ll> &a, ll n){
    for(int i=0;i<n;i++){
        a[i] = INF;
    }
}
void print(vector<ll> &a, ll n){
    for(int i=0;i<n;i++){
        if(a[i]==INF){
            cout << -1 << " ";
        }else{
            cout << a[i] << " ";
        }
    }
    cout << "\n";
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    //vector<ll> dis(Maxn,INF);
    vector<ll> dis;
    int T,sub;
    cin >> T >> sub;
    while(T--){
        int n,m,k,U,V,W;
        cin >> n >> m >> k;
        //vector<vector<iPair>> e(n+1);
        vector<iPair> e[n+1];
        for(int i=0;i<m;i++){
            cin >> U >> V >> W;
            e[V-1].push_back({U-1,W});
        }
        if(k==1){
            dijkstra(e,0,n,dis);
            print(dis,n);
            //initial(dis,n);
        }else if(k==2){
            dijkstra(e,0,n,dis);
            //print(dis,n);
            vector<ll> tp = dis;
            //initial(dis,n);     
            dijkstra(e,n-1,n,dis);
            vector<ll> sumEdge;
            for(int i=0;i<n;i++){
                //sumEdge.push_back(dis[i]+tp[i]);
                if(tp[i] != INF && dis[i] != INF){
                    sumEdge.push_back(tp[i]+dis[i]);
                }else{
                    sumEdge.push_back(INF);
                }
            }
            //for(int i=0;i<n;i++) cout << sumEdge[i] << " ";
            //initial(dis,n);
            for(int i=0;i<n;i++){
                e[n].push_back({i,sumEdge[i]});
            }
            // for(int i=0;i<=n;i++){
            //     for(int j=0;j<e[i].size();j++){
            //         cout << i << " " << e[i][j].first << " " <<e[i][j].second << "\n";
            //     }
            //     cout << "\n";
            // }
            dijkstra(e,n,n+1,dis);
            print(dis,n);
        }
    }
}


