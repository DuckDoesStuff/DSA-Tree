#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

struct Node {
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
};

Node* createNode(int val) {
    Node* n = new Node;
    n->key = val;
    n->left = nullptr;
    n->right = nullptr;

    return n;
}

//LRN
void printPostOrder(Node* root) {
    if(root == nullptr) return;

    printPostOrder(root->left);
    printPostOrder(root->right);

    cout << root->key << " ";
}

//NLR
void printPreOrder(Node* root) {
    if(root == nullptr) return;

    cout << root->key << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

//LNR
void printInOrder(Node* root) {
    if(root == nullptr) return;

    printInOrder(root->left);
    cout << root->key << " ";
    printInOrder(root->right);
}

void BFS(Node* root) {
    if(root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if(temp->left != nullptr) q.push(temp->left);
        if(temp->right != nullptr) q.push(temp->right);
        cout << temp->key << " ";
    }
}

void DFS(Node* root) {
    if(root == nullptr) return;
    stack<Node*> stk;
    stk.push(root);
    while(!stk.empty()) {
        Node* temp = stk.top();
        stk.pop();
        cout << temp->key << " ";
        if(temp->right != nullptr) stk.push(temp->right);
        if(temp->left != nullptr) stk.push(temp->left);
    }
}

int height(Node* root) {
    if(root == nullptr) return -1;

    int maxLeft = height(root->left);
    int maxRight = height(root->right);
    int maxDepth = max(maxLeft, maxRight) + 1;
    return maxDepth;
}

int left_height(Node* root) {
    int h = 0;
    while(root) {
        h++;
        root = root->left;
    }
    return h;
}
int right_height(Node* root) {
    int h = 0;
    while(root) {
        h++;
        root = root->right;
    }
    return h;
}
int countNode(Node* root) {
    if(root == nullptr) return 0;
    int left = left_height(root);
    int right = right_height(root);

    if(left == right) return pow(2, left) - 1;
    return countNode(root->left) + countNode(root->right) + 1;
}
int countNode2(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNode2(root->left) + countNode2(root->right);
}

int sumNode(Node* root) {
    if(root == nullptr) return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

Node* search(Node* root, int x) {
    if(root == nullptr) return nullptr;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* p = q.front();
        q.pop();
        if(p->key == x) return p;
        if(p->left != nullptr) q.push(p->left);
        if(p->right != nullptr) q.push(p->right);
    }
    return nullptr;
}

int main() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    root->left->left->left = createNode(8);
    //          1
    //        /   \
    //       2     3
    //      / \   /  \
    //     4   5 6    7
    //    /
    //   8

    BFS(root);
    cout << endl;
    Node* p = search(root, 0);
    cout << p->key << endl;

    return 0;
}