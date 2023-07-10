#include<bits/stdc++.h>
using namespace std;

// #define int long long
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define ALL(X) X.begin(), X.end()
#define rALL(X) X.rbegin(), X.rend()
typedef long long loli;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<loli, loli> pll;
typedef pair<pll, pll> pllll;
typedef string str;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<loli> vl;
typedef vector<vl> vvl;
typedef vector<vvl> vvvl;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<ld> vld;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<str> vs;
#define maxn 200005
// int a[maxn];
// ifstream fin("test.in");
// ofstream fout("test.out");
bool ans = true;
bool e[18][18];
int deg[18];
int n,m;
bool k33(){
    vi is_end;
    for(int i = 1 ;i<=n;i++){
        if(deg[i]==3)is_end.pb(i);
    }
    if(is_end.size()!=6)return false;
    while(1){
        bool flag = true;
        for(int i =1;i<=n;i++){
            if(deg[i]==2){
                flag = false;
                deg[i]=0;
                int a = -1,b;
                for(int j =1;j<=n;j++){
                    if(e[i][j]){
                        if(a==-1)a = j;
                        else b = j;
                    }
                }
                e[i][b] = false;e[i][a] = false;e[a][i] = false;e[b][i] = false;
                e[a][b] = true;e[b][a]  =true;
            }
        }
        if(flag)break;
    }
    vi is_down;
    vi is_up;
    is_up.pb(is_end[0]);
    for(int i = 1 ;i<=5;i++){
        if(e[is_end[0]][is_end[i]])is_down.pb(is_end[i]);
        else is_up.pb(is_end[i]);
    }
    if(is_up.size()!=3||is_down.size()!=3)return false;
    int temp = 0;
    for(int i :is_up){
        for(int j:is_down){
            if(e[i][j])temp++;
        }
    }
    if(temp==9)return true;
    return false;
}
bool k5(){
    vi is_end;
    for(int i = 1 ;i<=n;i++){
        if(deg[i]==4)is_end.pb(i);
    }
    if(is_end.size()!=5)return false;
    while(1){
        bool flag = true;
        for(int i =1;i<=n;i++){
            if(deg[i]==2){
                flag = false;
                deg[i]=0;
                int a = -1,b;
                for(int j =1;j<=n;j++){
                    if(e[i][j]){
                        if(a==-1)a = j;
                        else b = j;
                    }
                }
                e[i][b] = false;e[i][a] = false;e[a][i] = false;e[b][i] = false;
                e[a][b] = true;e[b][a]  =true;
            }
        }
        if(flag)break;
    }
    int temp = 0;
    for(int i =0;i<5;i++){
        for(int j =0;j<5;j++){
            if(e[is_end[i]][is_end[j]]){
                temp++;
            }
        }
    }
    if(temp==20)return true;
    return false;
}
void _solve()
{

    ans = true;
    cin >> n >> m;
    vpii edge(m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> edge[i].first >> edge[i].second;
    }
    
    for(int i =1;i<(1<<m);i++){
        memset(e,false,sizeof(e));
		memset(deg,0,sizeof(deg));
			for(int j = 0; j < m; j++){
				if((i>> j) & 1){
                    int a= edge[j].first;
                    int b= edge[j].second;
                    e[a][b] = true;
                    deg[a]++;
                    e[b][a] = true;
                    deg[b]++;
                }
            }
            if(k5()||k33()){
                cout <<"No\n";
                return;
            }
    
    }
    cout << "Yes\n";
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while (_--)
    {
        _solve();
    }
}