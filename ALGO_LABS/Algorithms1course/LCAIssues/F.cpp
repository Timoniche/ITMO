#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
//11 + 1 + 1 + 2 ? 2 3 ? 1 3 ? 2 4 + 4 + 4 - 4 ? 5 6 ? 5 5
//Ans: 1 1 2 2 5
const int MAXN = 200010;
vector<int> adj[MAXN];
vector<int> depth;
vector<int> links; //ближайший неудаленный
vector<bool> isDeleted;
vector<vector<int>> dp;
unsigned int logN = 0;
 
 
int findNearest(int v) {
    if (!isDeleted[v]) {
        return v;
    }
    return links[v] = findNearest(links[v]);
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
    return findNearest(dp[v][0]);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    unsigned int m;
    cin >> m;
    logN = ceil(log2(m + 1));
    dp.resize(m + 1);
    links.resize(m + 1);
    links[1] = 1;
    for (int i = 0; i < m + 1; i++) {
        dp[i] = vector<int>();
        dp[i].resize(logN + 1);
    }
    int minVertexNumber = 2;
    depth.resize(m + 1);
    isDeleted.resize(m + 1);
    dp[1][0] = 1;
    depth[1] = 1;
    for (int i = 0; i < m; i++) {
        char charIn;
        cin >> charIn;
        switch (charIn) {
            //динамические двоичные подъемы
            case '+':
                int parent;
                cin >> parent;
                adj[parent].push_back(minVertexNumber);
                depth[minVertexNumber] = depth[parent] + 1;
                dp[minVertexNumber][0] = parent;
                links[minVertexNumber] = parent;
                for (int j = 1; j <= logN; j++) {
                    dp[minVertexNumber][j] = dp[dp[minVertexNumber][j - 1]][j - 1];
                }
                minVertexNumber++;
                break;
            case '-':
                int vDelete;
                cin >> vDelete;
                isDeleted[vDelete] = true;
                break;
            case '?':
                int u, v;
                cin >> u >> v;
                cout << lca(u, v) << endl;
                break;
        }
    }
    return 0;
}
