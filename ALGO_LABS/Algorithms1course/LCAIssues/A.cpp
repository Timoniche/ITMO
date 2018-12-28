#include <iostream>
#include <vector>
 
 
using namespace std;
//5 1 1 2 3 2 2 3 4 5 Ans: 1 1
//5 1 1 2 2 3 4 5 4 2 3 5 Ans: 2 2 1
const int INF = 2147483647;
const int MAXN = 200010;
vector<int> atree;
vector<int> adj[MAXN];
vector<int> eulerTour;
vector<int> firstInEuler;
vector<bool> isVisited;
vector<int> depth;
 
 
void build(int v, int tl, int tr) {
    if (tl == tr) {
        int tmp = eulerTour[tl];
        atree[v] = tmp;
        return;
    }
    int tm = tl + (tr - tl) / 2;
    build(2 * v, tl, tm);
    build(2 * v + 1, tm + 1, tr);
    int tmp;
    if (depth[atree[2 * v]] < depth[atree[2 * v + 1]]) {
        tmp = atree[2 * v];
    } else {
        tmp = atree[2 * v + 1];
    }
    atree[v] = tmp;
}
 
int min(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return INF;
    if (l == tl && r == tr) {
        return atree[v];
    }
    int tm = (tl + tr) / 2;
    int tmp1 = min(2 * v, tl, tm, l, min(r, tm));
    int tmp2 = min(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    if (tmp1 == INF) {
        return tmp2;
    }
    if (tmp2 == INF) {
        return tmp1;
    }
    if (depth[tmp1] < depth[tmp2]) {
        return tmp1;
    } else {
        return tmp2;
    }
}
 
void dfsTour(int v, int height) {
    depth[v] = height;
    isVisited[v] = true;
    firstInEuler[v] = eulerTour.size();
    eulerTour.push_back(v);
    for (int i = 0; i < adj[v].size(); i++) {
        int child = adj[v][i];
        if (!isVisited[child]) {
            dfsTour(child, height + 1);
            eulerTour.push_back(v);
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    unsigned int n;
    cin >> n;
    for (int i = 0; i < n + 1; i++) {
        adj[i] = vector<int>();
 
    }
    firstInEuler.resize(n + 1);
    isVisited.resize(n + 1);
    depth.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        adj[i] = vector<int>();
    }
    for (int i = 2; i <= n; i++) {
        int tmp;
        cin >> tmp;
        adj[tmp].push_back(i);
    }
    dfsTour(1, 1);
    atree.reserve(4 * eulerTour.size());
    build(1, 0, eulerTour.size() - 1);
 
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (firstInEuler[u] < firstInEuler[v]) {
            cout << min(1, 0, eulerTour.size() - 1, firstInEuler[u], firstInEuler[v]) << endl;
        } else {
            cout << min(1, 0, eulerTour.size() - 1, firstInEuler[v], firstInEuler[u]) << endl;
        }
    }
    return 0;
}
