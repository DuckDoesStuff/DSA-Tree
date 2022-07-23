#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

void levelOrder(Node* root);

Node* createNode(int data) {
    Node* p = new Node;
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

int height(Node* root) {
    if (root == NULL) return 0;
    int heightL = height(root->left);
    int heightR = height(root->right);
    return 1 + max(heightL, heightR);
}

void LeftR(Node* &root) {
    Node* p = root->right;
    root->right = p->left;
    p->left = root;
    root = p;
}

void RightR(Node* &root) {
    Node* p = root->left;
    root->left = p->right;
    p->right = root;
    root = p;
}

void balance(Node* &root) {
    if(root == NULL) return;
    int h = height(root->left) - height(root->right);

    if(h > 1) {
        // Left - Left
        if(height(root->left->left) >= height(root->left->right)) {
            RightR(root);
        }
        // Left - Right
        else if(height(root->left->left) < height(root->left->right)) {
            LeftR(root->left);
            RightR(root);
        }
    }else if (h < -1) {
        // Right - Right
        if(height(root->right->right) >= height(root->right->left)) {
            LeftR(root);
        }
        // Right - Left
        else if(height(root->right->right) < height(root->right->left)) {
            RightR(root->right);
            LeftR(root);
        }
    }
}

void insertAVL(Node* &root, int key) {
    if(root == NULL) {
        root = createNode(key);
        return;
    }

    if (key < root->key) 
        insertAVL(root->left, key);
    else if (key > root->key) 
        insertAVL(root->right, key);
    else {
        cout << key << " already exist" << endl;
        return;
    }
    if (root != NULL) balance(root);
}

Node* createTree(vector<int> arr, int n) {
    Node* root = NULL;
    for(int i = 0; i < n; i++) {
        // levelOrder(root);
        // cout << endl << "Adding: " << arr[i] << endl;
        insertAVL(root, arr[i]);
    }
    return root;
}

Node* findMaxNode(Node* root) {
    while (root->right)
        root = root->right;
    return root;
}

void remove(Node* &root, int key) {
    if(root == NULL) return;

    if(key < root->key) remove(root->left, key);
    else if (key > root->key) remove(root->right, key);
    else {
        if(root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return;
        }else if (root->left && root->right) {
            Node* maxNode = findMaxNode(root->left);
            root->key = maxNode->key;
            remove(root->left, maxNode->key);
        }else {
            Node* child = root->left ? root->left : root->right;
            Node* temp = root;
            root = child;
            delete temp;
        }
    }
    
    balance(root);
}

void LNR(Node* root) {
    if(root == NULL) return;

    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

bool isAVL(Node* root) {
    if (root == NULL) return true;
    int leftH = height(root->left);
    int rightH = height(root->right);

    if (abs(leftH - rightH) <= 1 &&
        isAVL(root->left) && 
        isAVL(root->right)) 
            return true;
    
    return false;
}

void NLR(Node* root) {
    if(!root) return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

void levelOrder(Node* root) {
    if(root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* p = q.front();
        q.pop();

        cout << p->key << " ";
        if(p->left) q.push(p->left);
        if(p->right) q.push(p->right);
    }
}

int main() {
    vector<int> a =  {3, 4, 8, 1, 3, 9, 5, 4, 2, 0, -1};
    // vector<int> a = {10, 20, 30, 40, 50, 25};
    Node* root = createTree(a, a.size());

    cout << isAVL(root) << endl;
    levelOrder(root);
    cout << endl;

    remove(root, 4);

    cout << isAVL(root) << endl;
    levelOrder(root);
    // cout << endl;
    
    // LNR(root);

    return 0;
}