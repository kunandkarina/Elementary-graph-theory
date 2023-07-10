#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m; cin >> n >> m;
    //vector<vector<int>> map(n, vector<int>(m));
    vector<int> map[n];
    vector<int> degree(n,0);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        degree[u-1]++;
        degree[v-1]++;
    }
    sort(degree.begin(),degree.end());
    // for(int i=0;i<n;i++){
    //     cout << degree[i] << " ";
    // }
    cout << degree[0];
}