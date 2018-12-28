#include <limits>
#include <fstream>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct Node {
    int number;
    int key; //X
    int prior; //Y
    Node *left;
    Node *right;
    Node *prev;
 
    Node(int number, int key, int prior, Node *left, Node *right, Node *prev) : number(number), key(key), prior(prior),
                                                                                left(left), right(right), prev(prev) {}
 
    static bool compare(Node *i, Node *j) {
        return (i->key - j->key < 0);
    }
};
 
Node *root = nullptr;
 
int main() {
    std::ios_base::sync_with_stdio(false);
    int n = 0;
    cin >> n;
    Node *nodes[n];
    Node *nodesCopy[n];
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        nodes[i] = new Node(i + 1, a, b, nullptr, nullptr, nullptr);
        nodesCopy[i] = nodes[i];
    }
    //sort by x;
    sort(nodes, nodes + n, Node::compare);
 
    root = nodes[0];
    Node *nodeK = root; //k-й узел
    for (int i = 1; i < n; i++) {
        if (nodeK->prior < nodes[i]->prior) {
            nodeK->right = nodes[i];
            nodes[i]->prev = nodeK;
            nodeK = nodes[i];
        } else {
            Node *tmp = nodeK;
            nodeK = nodes[i];
            while (tmp->prior > nodes[i]->prior) {
                tmp = tmp->prev;
                if (tmp == nullptr) {
                    break;
                }
            }
            if (tmp == nullptr) {
                root->prev = nodes[i];
                nodes[i]->left = root;
                root = nodes[i];
            } else {
                nodes[i]->prev = tmp;
                nodes[i]->left = tmp->right;
                tmp->right->prev = nodes[i];
                tmp->right = nodes[i];
            }
        }
    }
    cout << "YES" << endl;
    //cout << nodes[nodesCopy[2]->key]->prev->number;
    for (int i = 0; i < n; i++) {
        int prevKey = 0, leftKey = 0, rightKey = 0;
        if (nodesCopy[i]->prev != nullptr) {
            prevKey = nodesCopy[i]->prev->number;
        } else {
            prevKey = 0;
        }
        if (nodesCopy[i]->left != nullptr) {
            leftKey = nodesCopy[i]->left->number;
        } else {
            leftKey = 0;
        }
        if (nodesCopy[i]->right != nullptr) {
            rightKey = nodesCopy[i]->right->number;
        } else {
            rightKey = 0;
        }
        cout << prevKey << " " << leftKey << " " << rightKey << endl;
    }
    return 0;
}
