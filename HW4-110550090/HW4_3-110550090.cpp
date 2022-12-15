#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1105;
const int M = 2e4 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
 
int head[N], tot, n, m, s, t;
struct Edge {
    int to, next, cap, flow;
}edge[M];
 
void init() {
    tot = 2;
    memset(head, -1, sizeof(head));
}
 
void addedge(int u, int v, int w, int rw = 0) {
    edge[tot].to = v;
    edge[tot].cap = w;
    edge[tot].flow = 0;
    edge[tot].next = head[u];
    head[u] = tot++;
 
    edge[tot].to = u;
    edge[tot].cap = rw;
    edge[tot].flow = 0;
    edge[tot].next = head[v];
    head[v] = tot++;
}
 
int Q[N];
int dep[N], cur[N], sta[N]; 
bool bfs(int s, int t, int n) {
    int fron = 0, tail = 0;
    memset(dep, -1, sizeof(dep[0]) * (n + 1));
    dep[s] = 0;
    Q[tail++] = s;
    while(fron < tail) {
        int u = Q[fron++];
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dep[v] == -1) {
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                Q[tail++] = v;
            }
        }
    }
    return false;
}
 
int dinic(int s, int t, int n) {
    int maxflow = 0;
    while(bfs(s, t, n)) {
        for(int i = 0; i <= n; ++i) cur[i] = head[i];
        int u = s, tail = 0;
        while(cur[s] != -1) {
            if(u == t) {
                int tp = inf;
                for(int i = tail - 1; i >= 0; --i)
                    tp = min(tp, edge[sta[i]].cap - edge[sta[i]].flow);
                maxflow += tp;
                for(int i = tail - 1; i >= 0; --i) {
                    edge[sta[i]].flow += tp;
                    edge[sta[i] ^ 1].flow -= tp;
                    if(edge[sta[i]].cap - edge[sta[i]].flow == 0)
                        tail = i;
                }
                u = edge[sta[tail] ^ 1].to;
            }
            else if(cur[u] != -1 && edge[cur[u]].cap > edge[cur[u]].flow && dep[u] + 1 == dep[edge[cur[u]].to]) {
                sta[tail++] = cur[u];
                u = edge[cur[u]].to;
            }
            else {
                while(u != s && cur[u] == -1)
                    u = edge[sta[--tail] ^ 1].to;
                cur[u] = edge[cur[u]].next;
            }
        }
    }
    return maxflow;
}
 
int main() {
    init();
    int v, w, nn, mm, k, cnt;
    scanf("%d%d%d", &nn, &mm, &k);
    n = nn + mm + 3;
    for(int u = mm + 1; u <= mm + nn; ++u) {
        scanf("%d", &cnt);
        for(int i = 1; i <= cnt; ++i) {
            scanf("%d", &v);
            addedge(u, v, 1);
        }
    }
    for(int u = 1; u <= mm; ++u)
        addedge(u, nn + mm + 2, 1);
    for(int v = mm + 1; v <= mm + nn + 1; ++v) {
        addedge(nn + mm + 1, v, 1);
        addedge(n, v, 1);
    }
    addedge(nn + mm + 1, n, k);
    printf("%d\n", dinic(n - 2, n - 1, n));
    return 0;
}