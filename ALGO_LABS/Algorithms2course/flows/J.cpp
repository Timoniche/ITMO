#include <vector>
#include <iostream>


using namespace std;

vector<bool> visited = vector<bool>(10005, false);
vector<long long> dis = vector<long long>(10005, 10000000005);
int n, weight;

struct barrier {
    long long x1, x2, y1, y2;

    barrier(long long x1, long long y1, long long x2, long long y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    barrier() {}
};

long long getSize(barrier f, barrier s) {
    long long res, h, v;
    v = f.y1 > s.y1 ? f.y1 - s.y2 : s.y1 - f.y2;
    h = f.x1 > s.x1 ? f.x1 - s.x2 : s.x1 - f.x2;
    res = max(h, v);
    return res < 0 ? 0 : res;
}

void goDejkstra(vector<vector<long long>> &data) {
    dis[0] = 0;
    for (int i = 0; i < n + 2; ++i) {
        long long min_v = -1;
        for (int j = 0; j < n + 2; ++j) {
            if (!visited[j] && (min_v == -1 || dis[j] < dis[min_v])) {
                min_v = j;
            }
        }
        visited[min_v] = true;
        for (int u = 0; u < n + 2; ++u) {
            if (min_v != u) {
                long long extra = data[min_v][u];
                if (dis[min_v] + extra < dis[u]) {
                    dis[u] = dis[min_v] + extra;
                }
            }
        }
    }
}

int main() {
    //freopen("t.txt", "r", stdin);
    //freopen("planaritycheck.out", "weight", stdout);
    cin >> n >> weight;
    vector<vector<long long>> vertex = vector<vector<long long>>(static_cast<unsigned long>(n + 2), vector<long long>(static_cast<unsigned long>(n + 2)));
    vector<barrier> barriers = vector<barrier>(static_cast<unsigned long>(n));
    for (int i = 0; i < n; ++i) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        barriers[i] = barrier(x1, y1, x2, y2);
    }
    vertex[0][n + 1] = weight;
    vertex[n + 1][0] = weight;
    for (int i = 0; i < n; ++i) {
        long long miny, maxy;
        barrier cRectangle = barriers[i];
        maxy = max(cRectangle.y1, cRectangle.y2);
        miny = min(cRectangle.y1, cRectangle.y2);
        vertex[0][i + 1] = vertex[i + 1][0] = weight - maxy;
        vertex[n + 1][i + 1] = vertex[i + 1][n + 1] = miny;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            vertex[i + 1][j + 1] = vertex[j + 1][i + 1] = getSize(cRectangle, barriers[j]);
        }
    }
    goDejkstra(vertex);
    auto& diiis = dis;
    if (dis[n + 1] != 10000000005) {
        cout << dis[n + 1];
    } else {
        cout << 0;
    }
    return 0;
}