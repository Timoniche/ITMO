#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

bool adjMatrix[6][6]{};
std::vector<int> adj[6];

void clean() {
    for (int i = 0; i < 6; ++i) { //NOLINT
        for (int j = 0; j < 6; ++j) {
            adjMatrix[i][j] = false;
        }
    }
    for (int i = 0; i < 6; ++i) { //NOLINT
        adj[i].clear();
    }
}

void init(int n, std::string& s) {
    int si = 0;
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < j; ++i) {
            bool tmp = (s[si++] == '1');
            if (tmp) {
                adjMatrix[i][j] = adjMatrix[j][i] = tmp;
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

bool check5() {
    bool not_planar = true;
    for (int j = 0; j < 5; ++j) {
        if (adj[j].size() != 4) {
            not_planar = false;
            break;
        }
    }
    return not_planar;
}

bool checkUnderK5(int extra) {
    bool not_planar = true;
    std::vector<int> d;
    for (int i = 0; i < 6; ++i) {
        if (i != extra) {
            if (adjMatrix[i][extra]) {
                d.push_back((int) adj[i].size() - 1);
            } else {
                d.push_back((int) adj[i].size());
            }
        }
    }
    for (auto u : d) {
        if (u < 4) {
            return false;
        }
    }
    return not_planar;
}

bool check5Connect(int con) {
    bool not_planar = true;
    int v1 = adj[con][0];
    int v2 = adj[con][1];
    std::vector<int> d;
    for (int i = 0; i < 6; ++i) {
        if (i != v1 && i != v2 && i != con) {
            if (adjMatrix[i][con]) {
                d.push_back(adj[i].size() - 1);
            } else {
                d.push_back(adj[i].size());
            }
        }
    }
    if (adjMatrix[v1][v2]) {
        d.push_back(adj[v1].size() - 1);
        d.push_back(adj[v2].size() - 1);
    } else {
        d.push_back(adj[v1].size());
        d.push_back(adj[v2].size());
    }
    for (int u : d) {
        if (u < 4) return false;
    }
    return not_planar;
}

int main() {
    std::ifstream fin("planaritycheck.in");
    std::ofstream fout("planaritycheck.out");

    int t;
    fin >> t;
    std::string s;
    std::getline(fin, s);
    for (int i = 0; i < t; ++i) {
        clean();
        std::getline(fin, s);
        int len = (int) s.length();
        int n = (int) ((1 + sqrt(1 + 4 * 2 * len)) / 2);
        init(n, s);
        if (n <= 4) fout << "YES" << std::endl;
        if (n == 5) {
            if (check5()) fout << "NO" << std::endl;
            else fout << "YES" << std::endl;
        }
        if (n == 6) {
            bool not_planar = false;
            //K5 стягивание
            for (int ii = 0; ii < 6; ++ii) {
                if (adj[ii].size() == 2) {
                    not_planar |= check5Connect(ii);
                }
            }
            //K5 - образуется без одной вершины
            for (int i1 = 0; i1 < 6; ++i1) {
                not_planar |= checkUnderK5(i1);
            }

            //K33
            for (int l = 0; l < 6; ++l) {
                for (int j = 0; j < 6; ++j) {
                    for (int k = 0; k < 6; ++k) {
                        if (l != j && j != k && l != k) {
                            if (adj[l].size() >= 3 && adj[j].size() >= 3 && adj[k].size() >= 3) {
                                //остальные 3 вершины
                                std::vector<int> tt;
                                for (int m = 0; m < 6; ++m) {
                                    if (m != l && m != j && m != k) {
                                        tt.push_back(m);
                                    }
                                }
                                if (adjMatrix[l][tt[0]] && adjMatrix[l][tt[1]] && adjMatrix[l][tt[2]] &&
                                        adjMatrix[j][tt[0]] && adjMatrix[j][tt[1]] && adjMatrix[j][tt[2]] &&
                                        adjMatrix[k][tt[0]] && adjMatrix[k][tt[1]] && adjMatrix[k][tt[2]]) {
                                    not_planar = true;
                                }
                            }
                        }
                    }
                }
            }
            if (not_planar) fout << "NO" << std::endl;
            else fout << "YES" << std::endl;
        }
    }
    return 0;
}

