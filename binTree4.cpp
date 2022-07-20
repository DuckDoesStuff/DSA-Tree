#include <iostream>
#include <vector>

using namespace std;

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int key;
    int height = 0;
};

int height(Node* root) {
    if (root == nullptr) return 0;
    return root->height;
}

Node* createNode(int key) {
    Node* p = new Node;
    p->key = key;
    p->height = 1;
    return p;
}

Node* rightRotate(Node* &root) {
    Node* t = root->left;
    Node* T2 = root->right;

    t->right = root;
    root->left = T2;

    root->height = max(height(root->left), height(root->right)) + 1;

    t->height = max(height(t->left), height(t->left)) + 1;
}

Node* leftRotate(Node* &root) {
    Node* t = root->right;
    Node* T2 = root->left;

    root->right = T2;
    t->left = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    t->height = max(height(t->left), height(t->right)) + 1;
}

int getBalance(Node* root) {
    if(root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

Node* insert(Node* root, int key) {
    if (root == nullptr)
        return createNode(key);

    if(key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    //Left left case
    if(balance > 1 && key < root->left->key)
        return rightRotate(root);
    //Right right case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    //Left right case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right left case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* createTree(vector<int> a, int n){
    Node* root = nullptr;
    for(int i = 0; i < n; i++)
        root = insert(root, a[i]);
    return root;
}

void NLR(Node* root) {
    if (root == nullptr) return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

int main() {
    vector<int> a = {10, 20, 30, 40, 50, 25};
    Node* root = createTree(a, a.size());
    NLR(root);
    return 0;
}