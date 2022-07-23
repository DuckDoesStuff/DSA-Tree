#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left = NULL;
    Node* right = NULL;
};

Node* createNode(int key) {
    Node* p = new Node;
    p->key = key;
    return p;
}

void insert(Node* &root, int key) {
    if(root == NULL) {
        root = createNode(key);
        return;
    }

    Node* t = root; //To traverse in BST
    Node* prev = NULL; //Prev of "t"
    while(t) {
        prev = t;
        if (key < t->key) t = t->left;
        else if (key > t->key) t = t->right;
        else return;
    }

    if(key < prev->key) prev->left = createNode(key);
    else prev->right = createNode(key);
}

Node* createTree(vector<int> arr, int n) {
    Node* root = NULL;
    for(int i = 0; i < n; i++) 
        insert(root, arr[i]);
    return root;
}

void LNR(Node* root) {
    if(root == NULL) return;
    stack<Node*> s;
    Node* curr = root;
    
    while(curr || !s.empty()) {
        while(curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->key << " ";
        curr = curr->right;
    }
}

void NLR(Node* root) {
    if(root == NULL) return;

    stack<Node*> s;
    s.push(root);
    while(!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->key << " ";

        if(curr->right) s.push(curr->right);
        if(curr->left) s.push(curr->left);
    }
}

void LRN(Node* root) {
    if(root == NULL) return;
    stack<Node*> s;
    stack<Node*> out;
    s.push(root);
    while(!s.empty()) {
        Node* curr = s.top();
        out.push(curr);
        s.pop();

        if(curr->left) s.push(curr->left);
        if(curr->right) s.push(curr->right);
    }

    while(!out.empty()) {
        cout << out.top()->key << " ";
        out.pop();
    }
}

Node* search(Node* root, int key) {
    Node* curr = root;
    Node* prev = NULL;

    while(curr && curr->key != key) {
        if(key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return curr;
}

Node* findMaxNode(Node* root) {
    while(root->right)
        root = root->right;
    return root;
}

void remove(Node* &root, int key) {
    Node* curr = root;
    Node* parent = NULL;

    while(curr && curr->key != key) {
        parent = curr;
        if(key < curr->key) curr = curr->left;
        else curr = curr->right;
    }

    //Node doesn't exist in BST
    if(curr == NULL) return;

    //Case 1: No child
    if(curr->left == NULL && curr->right == NULL) {
        //If tree only has 1 node
        if(curr == root)
            root = NULL;
        else {
            if(parent->left == curr) parent->left = NULL;
            else parent->right = NULL;
        }
        delete curr;
    }//Case 2: Two child
    else if(curr->left && curr->right) {
        // Node* maxNode = curr->left;
        // Node* p = NULL;

        // //Find max node in left subtree and its parent
        // while(maxNode->right) {
        //     p = maxNode;
        //     maxNode = maxNode->right;
        // }

        Node* maxNode = findMaxNode(curr->left);
        int val = maxNode->key;
        remove(root, maxNode->key);//hmmm is this still recursion?
        curr->key = val;
    }//Case 3: One child
    else {
        Node* child = curr->left ? curr->left:curr->right;
        //If curr is root then set root as child and delete curr
        if(curr == root) 
            root = child;
        else {
            if(parent->left == curr) parent->left = child;
            else parent->right = child;
        }
        delete curr;
    }
}

void levelOrder(Node* root) {
    if(root == nullptr) return;
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
    vector<int> a = {3, 4, 8, 1, 9, 5, 2, 0, -1};
    Node* root = createTree(a, a.size());

    // LNR(root);//-1 0 1 2 3 4 5 8 9  
    // cout << endl;
    // NLR(root);//3 1 0 -1 2 4 8 5 9 
    // cout << endl;
    // LRN(root);//-1 0 2 1 5 9 8 4 3 
    // cout << endl;
    levelOrder(root);
    cout << endl;
    // cout << search(root, 8)->left->key << endl;
    remove(root, 0);
    levelOrder(root);
    // LNR(root);


    return 0;
}