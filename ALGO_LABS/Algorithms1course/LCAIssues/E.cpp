#include <iostream>
#include <vector>
 
using namespace std;
const int MAXN = 200010;
//9 3 2 4 2 1 2 5 1 1 6 7 6 6 8 8 9
//Possible answer: 0 1 2 2 1 1 6 6 8
//3 1 2 2 3
//Possible answer: 2 0 2
vector<bool> isVisited;
vector<int> adj[MAXN];
vector<int> subTreeSize;
vector<bool> isCut;
vector<int> ans;
unsigned int n;
 
void dfs(int v);
 
int centoidVertex(int v, int tmp) {
    int maxSubTree = 0;
    isVisited[v] = true;
    for (int u : adj[v]) {
        if (!isVisited[u]) {
            if (!isCut[u] && subTreeSize[u] > tmp / 2 &&
                subTreeSize[u] > subTreeSize[maxSubTree]) {
                maxSubTree = u;
            }
        }
    }
    if (maxSubTree == 0) {
        return v;
    } else {
        return centoidVertex(maxSubTree, tmp);
    }
}
 
//возвращает новый корень
int decomposition(int v) {
    int tmpSize;
    isVisited = vector<bool>();
    isVisited.resize(n + 1);
    dfs(v);
    tmpSize = subTreeSize[v];
    if (tmpSize == 1) {
        return v;
    }
    isVisited = vector<bool>();
    isVisited.resize(n + 1);
    int center = centoidVertex(v, tmpSize);
    isCut[center] = true;
    for (int u : adj[center]) {
        if (!isCut[u]) {
            ans[decomposition(u)] = center;
        }
    }
    return center;
}
 
void dfs(int v) {
    isVisited[v] = true;
    subTreeSize[v] = 1;
    for (int u : adj[v]) {
        if (!isVisited[u] && !isCut[u]) {
            dfs(u);
            subTreeSize[v] += subTreeSize[u];
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    isVisited.resize(n + 1);
    subTreeSize.resize(n + 1);
    isCut.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        adj[i] = vector<int>();
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    ans.resize(n + 1);
    decomposition(1);
 
 
    for (int i = 1; i < n + 1; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
