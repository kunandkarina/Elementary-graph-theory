#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
vector<int> t[maxn];

void addEdge(int a, int b){
    t[a].push_back(b);
    t[b].push_back(a);
}
int main(){
    int n;
    cin >> n;
    vector<int> deg(n), vis(n), cnt(n);    //deg連node數 vis紀錄bfs走過沒 cnt是joint上面node的數量
    for(int i=0;i<n-1;i++){
        int a,b;
        cin >> a >> b;
        addEdge(a,b);
        deg[a]++;
        deg[b]++;
    }
    queue<int> q;                         // joint的邊vis[i] = 2, 其他的node vis[i]=0, 走訪過後vis[i]=1;
    for(int i=0;i<n;i++){
        if(deg[i]==1){
            q.push(i);
            cnt[i] = 1;
            vis[i] = 1;
        }
        if(deg[i]==3){
            vis[i] = 2;
        }
    }
    while(!q.empty()){            //bfs  找出simple path, 先從leaf開始做起，最後圖會變成頭尾為joint的simple path圖
        int x = q.front();
        q.pop();
        for(int y=0;y<t[x].size();y++){    //和x相連的邊
            if(vis[t[x][y]] != 1){
                deg[t[x][y]]--;
                deg[x]--;
                if(vis[t[x][y]]==0 && deg[t[x][y]] == 1){
                    vis[t[x][y]] = 1;
                    cnt[t[x][y]] = cnt[x] + 1;
                    q.push(t[x][y]);
                }
            }
        }
    }                                                          //vis[i]=0 代表夾在兩個joint之間，deg[i]!=0代表是simple path的道路
    vector<int> pos;       // 存放simple path的頭和尾的node
    for(int i=0;i<n;i++){
        if(deg[i]<=1 && vis[i]==2){
            pos.push_back(i);         //simple path的頭跟尾
        }
    }
    int m;
    cin >> m;
    vector<int> key(m);
    for(int i=0;i<m;i++){
        cin >> key[i];
    }
    if(pos.size()==1){         //判斷一個joint的情形
        if(m!=1){
            cout << "NO\n";
            return 0;
        }
        set<int> s;
        for(int y=0;y<t[pos[0]].size();y++){
            if(vis[t[pos[0]][y]]==1){
                s.insert(cnt[t[pos[0]][y]]);
            }
        }
        if(s.count(key[0])){
            cout << "YES\n";
            return 0;
        }
    }
    else{                                //判斷有頭尾joint的情形
        for(int i=0;i<2;i++){
            int pre = -1;
            vector<int> ans;
            q.push(pos[i]);
            while(!q.empty()){           //ans[]是用來存除了simple path以外node的cnt[]數，也就是可能的密碼
                int x = q.front();
                q.pop();
                for(int y=0;y<t[x].size();y++){
                    if(vis[t[x][y]]==1){
                        ans.push_back(cnt[t[x][y]]);
                    }
                    if(t[x][y] == pre || vis[t[x][y]] == 1) continue;
                    q.push(t[x][y]);
                }
                pre = x;
            }
            bool flag = false;             //判斷是否為密碼
            if(ans.size() == m+2){
                if(ans[0]==key[0] || ans[1] == key[0]){
                    if(ans[m+1] == key[m-1] || ans[m] == key[m-1]){
                        flag = true;
                        for(int i=1;i<m-1;i++){
                            if(key[i] != ans[i+1]){
                                flag = false;
                                break;
                            }
                        }
                    }
                }
            }
            if(flag){
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
    return 0;
}