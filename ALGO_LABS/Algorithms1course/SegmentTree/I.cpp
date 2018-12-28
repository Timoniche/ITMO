#include <limits>
#include <string>
#include <fstream>
#include <iostream>
 
using namespace std;
 
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
 
class Node {
public:
    int maxH;
    int sumIncline;
    bool isSet;
    int setIncline;
    Node *left;
    Node *right;
 
    Node(int maxH,
    int sumIncline,
    bool isSet,
    int setIncline,
    Node *left,
    Node *right)
    {
        this->isSet = isSet;
        this->maxH = maxH;
        this->sumIncline = sumIncline;
        this->left = left;
        this->right = right;
        this->setIncline = setIncline;
    }
};
 
void push(Node* v, int tl, int tr) {
    if (v->isSet) {
        int tm = tl + (tr - tl) / 2;
        v->isSet = false;
        int set = v->setIncline;
        int maxL = (tm - tl + 1) * v->setIncline;
        int maxR = (tr - (tm + 1) + 1) * v->setIncline;
        if (v->left == nullptr) {
            v->left = new Node(maxL, maxL, true, set, (Node*) nullptr, (Node*) nullptr);
        } else {
            v->left -> sumIncline = v->left -> maxH = maxL;
            v->left -> setIncline = set;
            v->left -> isSet = true;
        }
        if (v->right == nullptr) {
            v->right = new Node(maxR, maxR, true, set, nullptr, nullptr);
        } else {
            v->right -> sumIncline = v->right -> maxH = maxR;
            v->right -> setIncline = set;
            v->right -> isSet = true;
        }
    } else {
        if (v->left == nullptr) {
            v->left = new Node(0, 0, false, 0, nullptr, nullptr);
        }
        if (v->right == nullptr) {
            v->right = new Node(0, 0, false, 0, nullptr, nullptr);
        }
    }
}
 
void setD(Node* v, int tl, int tr, int l, int r, int D) {
    if (l > r) {
        return;
    }
    if (l == tl && r == tr) {
        int max = (tr - tl + 1) * D;
        v -> sumIncline = v -> maxH = max;
        v -> setIncline = D;
        v -> isSet = true;
        return;
    }
    push(v, tl, tr);
    int tm = tl + (tr - tl) / 2;
    setD(v -> left, tl, tm, l, MIN(tm, r), D);
    setD(v->right, tm + 1, tr, MAX(l, tm + 1), r, D);
    int max = MAX(v->left -> maxH, v->left -> sumIncline + v->right -> maxH);
    int sum = v->left -> sumIncline + v->right -> sumIncline;
    v->maxH = max;
    v->sumIncline = sum;
}
 
int countH(Node* v, int tl, int tr, int h) {
    if (tl == tr) {
        if (v->maxH > h) return tl;
        return tl + 1;
    }
    push(v, tl, tr);
    int tm = tl + (tr - tl) / 2;
    if (v->left -> maxH > h) {
        return countH(v->left, tl, tm, h);
    } else {
        return countH(v->right, tm + 1, tr, h - v->left -> sumIncline);
    }
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    Node* glava = new Node(0, 0, false, 0, nullptr, nullptr);
    int n;
    cin >> n;
    while (true) {
        string sin;
        cin >> sin;
        char c = sin[0];
        if (c == 'I') {
            int a, b, D;
            cin >> a >> b >> D;
            setD(glava, 0, n - 1, a - 1, b - 1, D);
        }
        if (c == 'Q') {
            int h;
            cin >> h;
            cout << countH(glava, 0, n - 1, h) << endl;
        }
        if (c == 'E') {
            break;
        }
    }
}
