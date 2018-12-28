#include <limits>
#include <fstream>
#include <iostream>
 
using namespace std;
 
struct Node {
    int key; //X
    int prior; //Y
    int weight;
    Node *left;
    Node *right;
 
    Node(int key, int prior, int weight, Node *left, Node *right) : key(key), prior(prior), weight(weight), left(left),
                                                                    right(right) {}
};
 
Node *root = nullptr;
 
int weightOf(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->weight;
}
 
int countWeight(Node *node) {
    return node->weight = weightOf(node->left) + weightOf(node->right) + 1;
}
 
pair<Node *, Node *> split(int x, Node *in) {
    pair<Node *, Node *> tmp;
    if (in == nullptr) {
        return make_pair(nullptr, nullptr);
    }
    if (x > in->key) {
        tmp = split(x, in->right);
        in->right = tmp.first;
        tmp.first = in;
        countWeight(tmp.first);
        return tmp;
    } else {
        tmp = split(x, in->left);
        in->left = tmp.second;
        tmp.second = in;
        countWeight(tmp.second);
        return tmp;
    }
}
 
Node *find(Node *node, int keyX) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == keyX) {
        return node;
    }
    if (node->key > keyX) {
        return find(node->left, keyX);
    }
    return find(node->right, keyX);
}
 
bool exists(int x) {
    Node *tmp = find(root, x);
    return tmp != nullptr;
}
 
Node *merge(Node *n1, Node *n2) {
    Node *ans;
    if (n1 == nullptr) {
        return n2;
    }
    if (n2 == nullptr) {
        return n1;
    }
    if (n1->prior > n2->prior) {
        n1->right = merge(n1->right, n2);
        ans = new Node(n1->key, n1->prior, 1, n1->left, n1->right);
    } else {
        n2->left = merge(n1, n2->left);
        ans = new Node(n2->key, n2->prior, 1, n2->left, n2->right);
    }
    countWeight(ans);
    return ans;
}
 
Node *insert(int x) {
    if (exists(x)) {
        return nullptr;
    }
    pair<Node *, Node *> tmp = split(x, root);
    Node *l = tmp.first;
    Node *r = tmp.second;
    Node *medium = new Node(x, rand(), 1, nullptr, nullptr);
    return root = merge(merge(l, medium), r);
}
 
Node *cut(int x) {
    pair<Node *, Node *> tmp = split(x, root);
    pair<Node *, Node *> tmpR = split(x + 1, tmp.second);
    return root = merge(tmp.first, tmpR.second);
}
 
int kMax(int k) {
    k--;
    Node *tmp = root;
    int prefSize = 0;
    while (tmp != nullptr) {
        prefSize = weightOf(tmp->right);
        if (prefSize == k) {
            return tmp->key;
        }
        if (prefSize < k) {
            tmp = tmp->left;
            k -= prefSize + 1;
        } else {
            tmp = tmp->right;
        }
    }
    return -7;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    int in;
    for (int i = 0; i < n; i++) {
        cin >> s;
        cin >> in;
        switch (s[0]) {
            case '+':
                insert(in);
                break;
            case '1':
                insert(in);
                break;
            case '-':
                cut(in);
                break;
            case '0':
                cout << kMax(in) << endl;
                break;
            default:
                break;
        }
    }
}
