#include <iostream>
#include <queue>

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

void insert(Node* &root, int key) {
    if (root == nullptr) root = createNode(key);
    else {
        if (key > root->key) insert(root->right, key);
        else if (key < root->key) insert(root->left, key);
        else return;
    }
}

Node* createTree(vector<int> arr, int n) {
    Node* root = nullptr;
    for(int i = 0; i < n; i++)
        insert(root, arr[i]);
    return root;
}

void NLR(Node* root) {
    if(root == nullptr) return;

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

void LevelOrder(Node* root) {
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

int countNode(Node* root) {
    if (root == nullptr) return 0;
    else return countNode(root->left) + countNode(root->right) + 1;
}

int height(Node* root) {
    if (root == nullptr) return 0;
    int leftH = height(root->left);
    int rightH = height(root->right);
    return max(leftH, rightH) + 1;
}

int sumNode(Node* root) {
    if (root == nullptr) return 0;
    else return root->key + sumNode(root->left) + sumNode(root->right);
}

Node* search(Node* root, int key) {
    if(root == nullptr || root->key == key) return root;
    if(key < root->key) search(root->left, key);
    else search(root->right, key);
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
        //Không có child thì xóa node root rồi set nó = null là được rồi
        if(root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }//Có 2 child thì tìm node LỚN NHẤT bên TRÁI hoặc node BÉ NHẤT bên PHẢI
        //Thay giá trị của node root bằng giá trị của node max ở bên trái
        //Xóa node max đó đi
        else if (root->left && root->right){
            Node* maxNode = findMaxNode(root->left);
            root->key = maxNode->key;
            remove(root->left, maxNode->key);
        }//Một child thì chọn child trái hoặc child phải
        //Thay root bằng child rồi xóa root CŨ
        else {
            Node* child = root->left ? root->left:root->right;
            Node* temp = root;
            root = child;
            delete temp;
        }
    }
}

void removeTree(Node* &root) {
    if(root == nullptr) return;
    removeTree(root->left);
    removeTree(root->right);
    delete root;
    root = nullptr;
}

int heightNode(Node* root, int key)
{   
	if (root == nullptr) return 0;
    // Tìm node cần tính chiều cao trước
	root = search(root, key);
	if (root)
		return height(root);
	return -1;
}

int find(Node *root, Node *p, int depth) {
	if (root == nullptr)
		return 0;
	if (root == p)
		return depth;
	int x = find(root->left, p, depth + 1);
	if (x != 0)
		return x;
	x = find(root->right, p, depth + 1);
	return x;
}//Tim level
int depthNode(Node* root, Node* p) {
	if (root == nullptr)
		return 0;
	int depth = 1;
	return find(root, p, depth);
}

bool checkTree(Node* root) {
	if (root->left != NULL && root->left->key > root->key) return false;
	if (root->right != NULL && root->right->key < root->key) return false;
	return root->left == NULL ? 1 : checkTree(root->left) && root->right == NULL ? 1 : checkTree(root->right);
}

bool isBST(Node* root) {
	if (root == NULL) return true;
	if (root->left != NULL) {
		Node*pL = root->left;//Tìm node lớn nhất bên trái
		while (pL->right != NULL) {
			pL = pL->right;
		}
		if (pL->key > root->key) return false;
			//Nếu node lớn nhất bên trái > root thì k phải cây
	} 
	if (root->right != NULL) {
		Node*pR = root->right;//Tìm node bé nhất bên phải
		while (pR->left != NULL) {
			pR = pR->left;
		}
		if (pR->key < root->key) return false;
			//Nếu node bé nhất bên phải < root thì k phải cây
	}
	return checkTree(root);
}

bool isFullBst(Node* root){
	if (isBST(root) == false) return false;
	if (root == NULL) return true;
	//Nếu cây không có con thì True
	if (root->left == NULL && root->right == NULL) return true;
	//Nếu cây có 2 con thì kiểm tra cây trái và cây phải
	if (root->left && root->right) return isFullBst(root->left) && isFullBst(root->right);
	return false;
}

int main () {
    vector<int> arr = {3, 4, 8, 1, 9, 5, 2, 0, -1};
    Node* root = createTree(arr, arr.size());
    // root->left->right->key = 1000;
    LevelOrder(root);
    cout << endl;
    // cout << height(root) << endl;
    // cout << search(root, 8)->left->key << endl;
    // cout << heightNode(root, 8) << endl;
    // cout << heightNode(root, 3) << endl;
    // cout << depthNode(root, root) << endl;
    // cout << isBST(root) << endl;
    return 0;
}