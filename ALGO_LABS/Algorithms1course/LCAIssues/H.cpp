#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
 
//5 2 1 3 2 0 3 3 3 2 1 Ans: 1 2 3 1 1
 
const int MAXN = 1000010;
vector<int> adj[MAXN];
vector<int> subColors;
vector<int> color;
vector<int> parent;
vector<int> last;
vector<int> depth;
vector<vector<int>> dp;
int root = 0;
int logN;
 
void dfsDepth(int v, int height) {
    depth[v] = height;
    for (int i = 0; i < adj[v].size(); i++) {
        int child = adj[v][i];
        dfsDepth(child, height + 1);
    }
}
 
int lca(int v, int u) {
    if (v == u) {
        return v;
    }
    if (depth[v] > depth[u]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    for (int i = logN; i >= 0; i--) {
        if (depth[dp[u][i]] - depth[v] >= 0) {
            u = dp[u][i];
        }
    }
    if (v == u) {
        return v;
    }
    for (int i = logN; i >= 0; i--) {
        if (dp[v][i] != dp[u][i]) {
            v = dp[v][i];
            u = dp[u][i];
        }
    }
    return parent[v];
}
 
void dfs(int v) {
    for (int i = 0; i < adj[v].size(); i++) {
        int child = adj[v][i];
        dfs(child);
        subColors[v] += subColors[child];
    }
    if (last[color[v]] != -1) {
        subColors[lca(v, last[color[v]])]--;
    }
    last[color[v]] = v;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    unsigned int n;
    cin >> n;
    logN = ceil(log2(n + 1));
    subColors.resize(n + 1);
    color.resize(n + 1);
    last.resize(n + 1);
    parent.resize(n + 1);
    depth.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        dp[i] = vector<int>();
        dp[i].resize(logN + 1);
    }
 
    for (int i = 0; i < n + 1; i++) {
        adj[i] = vector<int>();
    }
 
    for (int i = 1; i <= n; i++) {
        int p, c;
        cin >> p >> c;
        if (p != 0) {
            adj[p].push_back(i);
            parent[i] = p;
        } else {
            root = i;
        }
        color[i] = c;
        subColors[i] = 1;
    }
    parent[root] = root;
    for (int i = 1; i < n + 1; i++) {
        dp[i][0] = parent[i];
    }
    for (int j = 1; j <= logN; j++) {
        for (int i = 1; i < n + 1; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    for (int i = 0; i <= n; i++) {
        last[i] = -1;
    }
    dfsDepth(root, 1);
    dfs(root);
    for (int i = 1; i <= n; ++i) {
        cout << subColors[i] << " ";
    }
    return 0;
}
