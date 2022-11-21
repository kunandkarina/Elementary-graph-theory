#include<bits/stdc++.h>
using namespace std;

long long parent[100005];

struct node{
    long long u,v,w;
};

long long find(long long u){
    if(u!=parent[u]){
        parent[u] = find(parent[u]);
    }
    return parent[u];
}
bool mycompare(node a, node b){
    return a.w < b.w;
}
void kruskal(vector<node> &arr, int n){
    sort(arr.begin(), arr.end(), mycompare);
    for(int i=0;i<n;i++){
        parent[i] = i;
    }
    long long weight = 0;
    long long N = arr.size();
    long long edge_cnt = 0;
    for(int i=0;i<N;i++){
        long long eu = find(arr[i].u), ev = find(arr[i].v);
        if(eu == ev) continue;
        weight += arr[i].w;
        parent[ev] = eu;
        edge_cnt++;
        if(edge_cnt == n-1) break;
    }
    cout << weight << "\n";
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int Q; 
    cin >> Q;
    for(int k=0;k<Q;k++){
        long long n,m;
        cin >> n >> m;
        vector<int> a;
        for(int i=0;i<n;i++){
            long long k;
            cin >> k;
            a.push_back(k);
        }
        long long min_weight = a[0];
        long long min_index = 0;
        for(int i=0;i<n;i++){
            if(a[i]<min_weight) min_weight = a[i], min_index = i;
        }
        vector<node> arr;
        for(int i=0;i<n;i++){
            struct node tp = { min_index, i , a[min_index] + a[i]};
            arr.push_back(tp);
        }
        for(int i=0;i<m;i++){
            long long u,v,w;
            cin >> u >> v >> w;
            arr.push_back({u-1,v-1,w});
        }
        kruskal(arr,n);
    }
}