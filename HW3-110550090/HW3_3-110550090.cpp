#include<iostream>
#include<vector>
using namespace std;
#define Maxn 300005
#define level 19
vector<int> height(Maxn);
vector<vector<int>> parent(Maxn, vector<int>(level,-1));

int  heights(int root, int prev, vector<int> *t){
    int ans = 0;
    parent[root][0] = prev;
    for(int i=0;i<t[root].size();i++){
        if(t[root][i]!=prev){
            ans = max(ans, heights(t[root][i],root,t));
        }
    }
    return height[root] = 1 + ans;
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

    heights(1,0,t);
    parent[1][0] = -1;
    for(int i=1;i<=n;i++){
        cout << height[i]-1 << " " << parent[i][0] << "\n";
    }
}