#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX = 2e5 + 5;
struct edge{
    int fr,to;
    ll w;
    int ne;
};

struct Graph{
    struct Point{
        int pos;
        ll c;
        Point(){}
        Point(int pos, ll c):pos(pos),c(c){}
        bool operator<(const Point b) const{
            return c > b.c;
        }
    };
    edge e[MAX];
    int tot = 0;
    int head[MAX], id[MAX];
    bool vis[MAX];
    ll d[MAX];
    void add(int u,int v,ll w){
        e[tot].fr = u;
        e[tot].to = v;
        e[tot].ne = head[u];
        e[tot].w = w;
        head[u] = tot++;
    }

    void Dijkstra(int st){
        priority_queue<Point> pq;
        memset(d,0x3f,sizeof d);
        memset(vis,0,sizeof vis);
        d[st] = 0;
        pq.push(Point(st,0));
        while(pq.size()){
            Point cur = pq.top();
            pq.pop();
            if(vis[cur.pos]) continue;
            vis[cur.pos] = 1;
            for(int i=head[cur.pos]; ~i; i=e[i].ne){
                if(d[e[i].to] > d[cur.pos] + e[i].w){
                    d[e[i].to] = d[cur.pos] + e[i].w;
                    pq.push(Point(e[i].to, d[e[i].to]));
                }
            }
        }
    }

    int clk = 0;
    int DFN[MAX], LOW[MAX], bi[MAX];
    void id_add(int u,int v,ll w,int _id){
        e[tot].fr = u;
        e[tot].to = v; 
        e[tot].ne = head[u];
        e[tot].w = w;
        id[tot] = _id;
        head[u] = tot++;
    }

    void tarjan(int x, int rt){
        DFN[x] = LOW[x] = ++clk;
        for(int i=head[x]; ~i; i=e[i].ne){
            if(e[i].to == rt) continue;
            if(!DFN[e[i].to]){
                tarjan(e[i].to, x);
                LOW[x] = min(LOW[x],LOW[e[i].to]);
                if(LOW[e[i].to] > DFN[x]){
                    bi[id[i]] = 1;
                }
            }
            else LOW[x] = min(LOW[x],DFN[e[i].to]);
        }
    }

    void init(){
        tot = 0;
        clk = 0;
        memset(head,-1,sizeof head);
    }
} G1,G2,G3;

int main(){
    int n,m;
    int u,v;
    ll w;
    cin >> n >> m;
    G1.init();
    G2.init();
    G3.init();
    for(int i=1;i<=m;i++){
        //cin >> u >> v >> w;
        scanf("%d%d%lld", &u,&v,&w);
        G1.add(u,v,w);
        G2.add(v,u,w);
    }
    G1.Dijkstra(1);
    G2.Dijkstra(2);
    ll DIS = G1.d[2];
    for(int i=0;i<G1.tot;i++){
        u = G1.e[i].fr;
        v = G1.e[i].to;
        w = G1.e[i].w;
        if(G1.d[u]+G2.d[v] + w == DIS){
            G3.id_add(u,v,w,i);
            G3.id_add(v,u,w,i);
        }
    }
    G3.tarjan(1,-1);
    for(int i=0;i<G1.tot;i++){
        u = G1.e[i].fr;
        v = G1.e[i].to;
        w = G1.e[i].w;
        if(G1.d[v]+G2.d[u] + w < DIS) puts("HAPPY");
        else if(G3.bi[i]) puts("SAD");
        else puts("SOSO");
    }
}