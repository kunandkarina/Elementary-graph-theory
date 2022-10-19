#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> arr(1001,vector<int>(1001,0));
    int n,m;
    cin >> n >> m;
    vector<int> indegree(1000,0);
    vector<int> outdegree(1000,0);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        arr[u-1][v-1] = w;
        indegree[u-1]++;
        outdegree[v-1]++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    for(int i=0;i<n;i++){
        cout << outdegree[i] << " " << indegree[i] << endl;
    }
}