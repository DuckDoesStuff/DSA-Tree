#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node{
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* createNode(int data) {
    Node* p = new Node;
    p->key = data;
    return p;
}

//Insert new node to binary search tree
void Insert(Node* &root, int x) {
    if(root == nullptr) {
        root = createNode(x);
        return;
    }
    if(x <= root->key) Insert(root->left, x);
    else Insert(root->right, x);
}

//Pre-order traversal
void NLR(Node* root) {
    if(root == nullptr) return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

//In-order traversal
void LNR(Node* root) {
    if(root == nullptr) return;

    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

//Post-order traversal
void LRN(Node* root) {
    if(root == nullptr) return;

    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

//Level-order traversal (using queue)
void LevelOrder(Node* root) {
    if(root == nullptr) return;
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

int Height(Node* root) {
    if(root == nullptr) return 0;
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int countNode(Node* root) {
    if(root == nullptr) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int sumNode(Node* root) {
    if(root == nullptr) return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

Node* Search(Node* root, int x) {
    if(x == root->key) return root;
    if(root->left == nullptr && root->right == nullptr) return nullptr;
    
    if (x < root->key) return Search(root->left, x);
    else return Search(root->right, x);
}

Node* findMaxNode(Node* root) {
    while(root->right)
        root = root->right;
    return root;
}

void Remove(Node* &root, int x) {
    if (root == nullptr) return;

    if(x < root->key) Remove(root->left, x);
    else if (x > root->key) Remove(root->right, x);
    else {
        //Case 1: No child
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        //Case 2: Two childs
        else if (root->left && root->right) {
            Node* max = findMaxNode(root->left);
            root->key = max->key;
            Remove(root->left, max->key);
        }
        //Case 3: One child
        else {
            Node* child = (root->left) ? root->left:root->right;//Choose a child
            Node* curr = root;
            root = child;
            delete curr;
        }
    }
}

Node* createTree(vector<int> a, int n) {
    Node* root = nullptr;
    for(int i = 0; i < n; i++)
        Insert(root, a[i]);
    return root;
}

void InsertLoop(Node* root, int x) {
    Node* p = createNode(x);
    Node* t = root;
    Node* y = nullptr;

    while(t != nullptr) {
        y = t;
        if(x <= t->key) t = t->left;
        else t = t->right;
    }
    if(y == nullptr) y = p;
    else if (x <= y->key) y->left = p;
    else y->right = p;

}

Node* createTreeLoop(vector<int> arr, int n) {
    Node* root = nullptr;
    for(int i = 0; i < n; i++) {
        InsertLoop(root, arr[i]);
    }
    return root;
}

void RemoveIterative(Node* &root, int x) {
    Node* curr = root;
    Node* prev = nullptr;

    while(curr && curr->key != x) {
        prev = curr;
        if(x < curr->key) curr = curr->left;
        else curr = curr->right;
    }

    if (curr == nullptr) return;

    //If has no or one child
    if (curr->left == nullptr || curr->right == nullptr) {
        Node* temp;

        //Choose a child
        if (curr->left) temp = curr->left;
        else temp = curr->right;

        if (prev == nullptr) {
            root = temp;
            return;
        }
        if (curr == prev->left) prev->left = temp;
        else prev->right = temp;

        delete curr;
    } else {//If has two childs
        Node* p = nullptr;
        Node* temp = curr->right;

        while (temp->left) {
            p = temp;
            temp = temp->left;
        }

        if (p) p->left = temp->right;
        else curr->right = temp->right;

        curr->key = temp->key;
        delete temp;
    }
    return;
}

int countLess(Node* root, int x) {
    if (root == nullptr) return 0;
    int count = 0;
    if (x > root->key) {
        count++;
        count += countLess(root->left, x);
        count += countLess(root->right, x);
    }else
        count += countLess(root->left, x);
    return count;
}

int countGreat(Node* root, int x) {
    if (root == nullptr) return 0;
    int count = 0;
    if (x < root->key) {
        count++;
        count += countGreat(root->left, x);
        count += countGreat(root->right, x);
    }else
        count += countGreat(root->right, x);
    return count;
}

bool isComplete(Node* root, int index, int n) {
    if (root == nullptr) return true;
    if (index >= n) return false;
    
    return  isComplete(root->left, 2 * index + 1, n) &&
            isComplete(root->right, 2 * index + 2, n);
}

int countLeaf(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    else return countLeaf(root->left) + countLeaf(root->right);
}

int main() {
    vector<int> arr = {3, 4, 8, 1, 3, 9, 5, 4, 2, 0, -1};
    Node* root = createTree(arr, arr.size());

    LevelOrder(root);
    cout << endl;
    // Remove(root, 5);
    // LevelOrder(root);
    // cout << endl;
    // cout << Height(root) << endl;
    // cout << countNode(root) << endl;
    // cout << sumNode(root) << endl;
    // cout << heightNode(root, 6) << endl;
    // cout << countLess(root, 7) << endl;
    // cout << countGreat(root, 4) << endl;
    // int index = 0;
    // int n = countNode(root);
    // cout << isComplete(root, index, n) << endl;
    // cout << countLeaf(root) << endl;
    cout << Search(root, 3)->key << endl;
    return 0;
}