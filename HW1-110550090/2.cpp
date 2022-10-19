#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;
    long long t;
    cin >> n >> m >> k >> t;
    vector<int>s[n];
    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        s[a-1].push_back(b-1);
    }
    queue<int> q;
    vector<bool> check(n,true);
    vector<int> dis(n,INT_MAX);
    for(int i=0;i<k;i++){
        int f;
        cin >> f;
        q.push(f-1);
        check[f-1] = false;
        dis[f-1] = 0;
    }

    while(!q.empty()){
        int tp = q.front();
        q.pop();
        for(int j=0;j<s[tp].size();j++){
            if(check[s[tp][j]]== true){
                q.push(s[tp][j]);
                check[s[tp][j]] = false;
                dis[s[tp][j]] = dis[tp] + 1;
            }
        }

    }
    int cnt = 0;
    for(int i=0;i<n;i++){
        if(dis[i]<t) cnt++;
    }
    cout << cnt;
}
