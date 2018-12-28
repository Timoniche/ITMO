#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
//5 1 1 2 3 2 2 3 4 5 Ans: 1 1
//5 1 1 2 2 3 4 5 4 2 3 5 Ans: 2 2 1
const int INF = 2147483647;
const int MAXN = 200010;
vector<int> adj[MAXN];
vector<int> parent;
vector<int> costEtoParent;
vector<int> depth;
vector<vector<int>> dp;
vector<vector<int>> minDp;
unsigned int logN = 0;
 
void dfs(int v, int height) {
    depth[v] = height;
    for (int i = 0; i < adj[v].size(); i++) {
        int child = adj[v][i];
        dfs(child, height + 1);
    }
}
 
static int lca(int v, int u) {
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
 
static int minEdgePath(int v, int u, int lcaUV) {
    int answer = INF;
    for (int i = logN; i >= 0; i--) {
        if (depth[dp[u][i]] >= depth[lcaUV]) {
            answer = min(answer, minDp[u][i]);
            u = dp[u][i];
        }
        if (depth[dp[v][i]] >= depth[lcaUV]) {
            answer = min(answer, minDp[v][i]);
            v = dp[v][i];
        }
 
    }
    return answer;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    unsigned int n;
    cin >> n;
    logN = ceil(log2(n + 1));
    for (int i = 0; i < n + 1; i++) {
        adj[i] = vector<int>();
    }
    dp.resize(n + 1);
    minDp.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        dp[i] = vector<int>();
        dp[i].resize(logN + 1);
        minDp[i] = vector<int>();
        minDp[i].resize(logN + 1);
    }
    parent.resize(n + 1);
    costEtoParent.resize(n + 1);
    depth.resize(n + 1);
    parent[1] = 1;
    costEtoParent[1] = INF;
    for (int i = 2; i <= n; i++) {
        int tmp;
        cin >> tmp;
        adj[tmp].push_back(i);
        parent[i] = tmp;
        cin >> tmp;
        costEtoParent[i] = tmp;
    }
    dfs(1, 1);
    for (int i = 1; i < n + 1; i++) {
        dp[i][0] = parent[i];
        minDp[i][0] = costEtoParent[i];
    }
    for (int j = 1; j <= logN; j++) {
        for (int i = 1; i < n + 1; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            minDp[i][j] = min(minDp[i][j - 1], minDp[dp[i][j - 1]][j - 1]);
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        int lcaUV = lca(v, u);
        cout << minEdgePath(v, u, lcaUV) << endl;
    }
    return 0;
}
