#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int key = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* createNode(int key) {
    Node* p = new Node;
    p->key = key;
    return p;
}

void insert(Node* &root, int key) {
    if (root == nullptr) root = createNode(key);
    else {
        if(key <= root->key) insert(root->left, key);
        else insert(root->right, key);
    }
}

Node* createTree(vector<int> a, int n){
    Node* root = nullptr;
    for(int i = 0; i < n; i++)
        insert(root, a[i]);
    return root;
}

void NLR(Node* root) {
    if (root == nullptr) return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

void LNR(Node* root) {
    if (root == nullptr) return;

    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

void LRN(Node* root) {
    if (root == nullptr) return;

    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

void levelOrder(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* p = q.front();
        q.pop();
        cout << p->key << " ";
        if(p->left != nullptr) q.push(p->left);
        if(p->right != nullptr) q.push(p->right);
    }
}

int countNode(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int height(Node* root) {
    if (root == nullptr) return 0;
    int leftH = height(root->left);
    int rightH = height(root->right);

    return max(leftH, rightH) + 1;
}

int sumNode(Node* root) {
    if (root == nullptr) return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

Node* search(Node* root, int key) {
    if (root == nullptr || root->key == key) return root;
    if (key < root->key) search(root->left, key);
    else search(root->right, key);
}

Node* findMax(Node* root) {
    while(root->right)
        root = root->right;
    return root;
}

void remove(Node* &root, int key) {
    if (root == nullptr) return;

    if (key < root->key) remove(root->left, key);
    else if (key > root->key) remove(root->right, key);
    else {
        //No child
        if(root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }   //Two child
        else if (root->left && root->right) {
            Node* maxNode = findMax(root->left);//find the max node in the left subtree
            root->key = maxNode->key;//replace current node with the max value
            remove(root->left, maxNode->key);//remove the max node in the left subtree
        }   //One child
        else {
            Node* child = root->left ? root->left:root->right;//Pick a child
            Node* temp = root;
            root = child;//Replace current node as child the delete the current node
            delete root;
        }
    }
}

int main() {
    vector<int> arr = {3, 4, 8, 1, 3, 9, 5, 4, 2, 0, -1};
    Node* root = createTree(arr, arr.size());
    // levelOrder(root);
    LNR(root);
    cout << endl;
    // cout << countNode(root) << endl;
    // cout << height(root) << endl;
    // cout << sumNode(root) << endl;
    // cout << search(root, 3)->key << endl;
    return 0;
}