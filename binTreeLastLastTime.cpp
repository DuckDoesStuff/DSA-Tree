#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* createNode(int key) {
    Node* p = new Node;
    p->key = key;
    return p;
}

void insert(Node* &root, Node* p) {
    if(root == nullptr) {
        root = p;
        return;
    }
    if(p->key <= root->key) insert(root->left, p);
    else insert(root->right, p);
}

Node* createTree(vector<int> a, int n) {
    Node* root = nullptr;
    for(int i = 0; i < n; i++) 
        insert(root, createNode(a[i]));
    return root;
}

void LNR(Node* root) {
    if(root == nullptr) return;

    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right); 
}

int height(Node* root) {
    if (root == nullptr) return 0;
    int heightL = height(root->left);
    int heightR = height(root->right);
    return max(heightL, heightR) + 1;
}

Node* search(Node* root, int key) {
    if(root == nullptr || root->key == key) return root;
    if(key < root->key) search(root->left, key);
    else search(root->right, key);
}

int countNode(Node* root) {
    if(root == nullptr) return 0;
    return countNode(root->left) + countNode(root->right) + 1;
}

int heightNode(Node* root, int key) {
    if (root == nullptr) return 0;
    root = search(root, key);
    return height(root);
}

Node* findMaxNode(Node* root) {
    while(root->right)
        root = root->right;
    return root;
}

void remove(Node* &root, int key) {
    if(root == nullptr) return;

    if(key < root->key) remove(root->left, key);
    else if (key > root->key) remove(root->right, key);
    else {
        if(root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
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
}

int countGreater(Node* root, int x) {
    if (root == nullptr) return 0;
    int count = 0;
    if (root->key > x) {
        count++;
        count += countGreater(root->left, x);
        count += countGreater(root->right, x);
    }else count += countGreater(root->right, x);
    return count;
}

int countLess(Node* root, int x) {
    if (root == nullptr) return 0;
    int count = 0;
    if (root->key < x) {
        count++;
        count += countLess(root->left, x);
        count += countLess(root->right, x);
    }else count += countLess(root->left, x);
    return count;
}

int find(Node* root, Node* p, int level) {
    if(root == nullptr) return 0;
    if(root == p) return level;//Nếu tìm được node thì trả về level
    int x = find(root->left, p, level + 1);//Đệ quy tìm node ở bên trái
    if (x != 0) return x;
    x = find(root->right, p, level + 1);
    return x;
}

int level(Node* root, Node* p) {
    if(root == nullptr) return 0;
    int level = 1;
    return find(root, p, level);
}

int countLeaf(Node* root) {
    if(root == nullptr) return 1;
    if(root->left == nullptr && root->right == nullptr) return 1;
    else return countLeaf(root->left) + countLeaf(root->right);
}

bool checkTree(Node* root) {
    if(root->left && root->left->key > root->key) return false;
    if(root->right && root->right->key < root->key) return false;
    return  root->left ? checkTree(root->left) : true &&
            root->right ? checkTree(root->right) : true;
}

bool isBST(Node* root) {
    if(root==nullptr) return true;
    if(root->left) {
        Node* MaxLeft = root->left;
        while(MaxLeft->right)
            MaxLeft = MaxLeft->right;
        if(MaxLeft->key > root->key) return false;
    }
    if(root->right) {
        Node* MinRight = root->right;
        while(MinRight->left)
            MinRight = MinRight->left;
        if(MinRight->key < root->key) return false;
    }
    return checkTree(root);
}

bool isFullBST(Node* root) {
    if(!isBST(root)) return false;
    if(root->left == nullptr && root->right == nullptr) return true;
    if(root->left && root->right) 
        return isFullBST(root->left) && isFullBST(root->right);
    return false;
}

bool identicalTree(Node* root1, Node* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 != nullptr && root2 != nullptr) {

        return  //root1->key == root2->key &&
                identicalTree(root1->left, root2->left) &&
                identicalTree(root1->right, root2->right);
    }
    return false;
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

void NLR(Node* root) {
    if(root == nullptr) return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

void LRN(Node* root) {
    if(root == nullptr) return;

    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

int main() {
    vector<int> a = {3, 4, 8, 1, 9, 5, 2, 0, -1};
    // vector<int> a = {1, 0, 3, -1};
    Node* root1 = createTree(a, a.size());

    // LNR(root1);
    // cout << endl;
    // NLR(root1);
    // cout << endl;
    // LRN(root1);
    // cout << endl;
    levelOrder(root1);
    cout << endl;
    
    // cout << endl;
    // vector<int> b = {2, 3, 4, 5};
    // Node* root2 = createTree(b, b.size());
    // LNR(root2);
    // cout << endl;
    // cout << identicalTree(root1, root2) << endl;
    // cout << heightNode(root, 8) << endl;
    // cout << height(root) << endl;
    // cout << search(root1, 8)->left->key << endl;
    remove(root1, 3);
    levelOrder(root1);
    
    return 0;
}