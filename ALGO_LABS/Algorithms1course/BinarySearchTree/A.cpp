#include <limits>
#include <fstream>
#include <iostream>
 
using namespace std;
 
//справа больше, слева меньше
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *prev;
 
    Node(int key, Node *left, Node *right, Node *prev) : key(key), left(left), right(right), prev(prev) {}
};
Node* root = nullptr;
 
Node* next(int x);
Node* prev(int x);
Node* find(Node *node, int keyX);
void cut(int x, Node *node) {
    Node *v;
    if (node == nullptr) {
        v = find(root, x);
    } else {
        v = node;
    }
    if (v == nullptr) {
        return;
    }
    Node *p = v->prev;
    if (v->left == nullptr && v->right == nullptr) {
        if (p == nullptr) {
            root = nullptr;
        } else if (p->left == v) {
            p->left = nullptr;
        } else {
            p->right = nullptr;
        }
    } else if (v->left == nullptr || v->right == nullptr) {
        if (p == nullptr) {
            if (v->left == nullptr) {
                v->right->prev = nullptr;
                root = v->right;
            } else {
                v->left->prev = nullptr;
                root = v->left;
            }
        } else if (v->left == nullptr) {
            if (p->left == v) {
                p->left = v->right;
            } else {
                p->right = v->right;
            }
            v->right->prev = p;
 
        } else {
            if (p->left == v) {
                p->left = v->left;
            } else {
                p->right = v->left;
            }
            v->left->prev = p;
        }
    } else {
        Node *suc = next(x);
        v->key = suc->key;
        cut(suc->key, suc);
    }
}
 
Node *minimum(Node *node) {
    if (node->left == nullptr) {
        return node;
    }
    return minimum(node->left);
}
 
Node *maximum(Node *node) {
    if (node->right == nullptr) {
        return node;
    }
    return maximum(node->right);
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
 
void insert(Node *node, int x) {
    if (node->key < x) {
        if (node->right != nullptr) {
            insert(node->right, x);
        } else {
            node->right = new Node(x, nullptr, nullptr, node);
        }
    } else if (node->key > x) {
        if (node->left != nullptr) {
            insert(node->left, x);
        } else {
            node->left = new Node(x, nullptr, nullptr, node);
        }
    }
}
 
bool exists(Node *node, int keyX) {
    Node *tmp = find(node, keyX);
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
                if (root != nullptr) {
                    insert(root, x);
                } else {
                    root = new Node(x, nullptr, nullptr, nullptr);
                }
                break;
            case 'd':
                cut(x, nullptr);
                break;
            case 'e':
                if (exists(root, x)) {
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
