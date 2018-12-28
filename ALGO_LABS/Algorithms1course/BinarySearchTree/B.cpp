#include <limits>
#include <fstream>
#include <iostream>
 
using namespace std;
 
struct Node {
    int key; //X
    int prior; //Y
    Node *left;
    Node *right;
 
    Node(int key, int prior, Node *left, Node *right) : key(key), prior(prior), left(left), right(right) {}
};
 
Node *root = nullptr;
 
pair<Node *, Node *> split(int x, Node *in) {
    pair<Node *, Node *> tmp;
    if (in == nullptr) {
        return make_pair(nullptr, nullptr);
    }
    if (x > in->key) {
        tmp = split(x, in->right);
        in->right = tmp.first;
        tmp.first = in;
        return tmp;
    } else {
        tmp = split(x, in->left);
        in->left = tmp.second;
        tmp.second = in;
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
 
Node *merge(Node* n1, Node* n2) {
    if (n1 == nullptr) {
        return n2;
    }
    if (n2 == nullptr) {
        return n1;
    }
    if (n1->prior > n2->prior) {
        n1->right = merge(n1->right, n2);
        return new Node(n1->key, n1->prior, n1->left, n1->right);
    } else {
        n2->left = merge(n1, n2->left);
        return new Node(n2->key, n2->prior, n2->left, n2->right);
    }
}
 
Node *insert(int x) {
    pair<Node*, Node*> tmp = split(x, root);
    Node *l = tmp.first;
    Node *r = tmp.second;
    Node *medium = new Node(x, rand(), nullptr, nullptr);
    return root = merge(merge(l, medium), r);
}
 
Node *cut(int x) {
    pair<Node*, Node*> tmp = split(x, root);
    pair<Node*, Node*> tmpR = split(x + 1, tmp.second);
    return root = merge(tmp.first, tmpR.second);
}
 
bool exists(int x) {
    Node *tmp = find(root, x);
    return tmp != nullptr;
}
 
Node *next(int x) {
    Node *cur = root;
    Node *succ = nullptr;
    while (cur != nullptr) {
        if (cur->key > x) {
            succ = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return succ;
}
 
Node *prev(int x) {
    Node *cur = root;
    Node *succ = nullptr;
    while (cur != nullptr) {
        if (cur->key < x) {
            succ = cur;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    return succ;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    string s;
    while (cin >> s) {
        Node *tmp;
        int x;
        cin >> x;
        switch (s[0]) {
            case 'i':
                insert(x);
                break;
            case 'd':
                cut(x);
                break;
            case 'e':
                if (exists(x)) {
                    cout << "true" << endl;
                } else {
                    cout << "false" << endl;
                }
                break;
            case 'n':
                tmp = next(x);
                if (tmp == nullptr) {
                    cout << "none" << endl;
                } else {
                    cout << tmp->key << endl;
                }
                break;
            case 'p':
                tmp = prev(x);
                if (tmp == nullptr) {
                    cout << "none" << endl;
                } else {
                    cout << tmp->key << endl;
                }
                break;
            default:
                exit(0);
        }
    }
}
