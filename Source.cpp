#include<iostream>
using namespace std;

struct NODE{
	int key;
	NODE* left;
	NODE* right;
};

NODE* createNode(int data){
	NODE *p = new NODE;
	p->key = data;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void Insert(NODE* &pRoot, int x){
	if (pRoot == NULL){
		pRoot = createNode(x);
		return;
	}
	if (pRoot->key == x){
		return;
	}
	if (pRoot->key > x){
		Insert(pRoot->left, x);
	}
	else{
		Insert(pRoot->right, x);
	}
}

NODE* createTree(int a[], int n){
	NODE* T = NULL;
	for (int i = 0; i < n; ++i){
		Insert(T, a[i]);
	}
	return T;
}

void LNR(NODE* pRoot){
	if (pRoot == NULL){
		return;
	}
	LNR(pRoot->left);
	cout << pRoot->key << " ";
	LNR(pRoot->right);
}

NODE* Search(NODE*pRoot, int x){
	if (pRoot == NULL) return NULL;
	if (pRoot->key == x) return pRoot;
	if (pRoot->key < x) return Search(pRoot->right, x);
	if (pRoot->key > x) return Search(pRoot->left, x);
}
NODE* findMin(NODE* root)
{
	NODE* p = root;
	while (p && p->left != NULL)
		p = p->left;
	return p;
}
void remove(NODE*& root, int x)
{
	if (root == NULL) return;

	if (root->key < x) {
		remove(root->right, x);
		return;
	}
	if (root->key > x) {
		remove(root->left, x);
		return;
	}

	if (root->left == NULL && root->right == NULL){
		root = NULL;
		return;
	}
	if (root->left == NULL){
		NODE* tmp = root;
		root = root->right;
		delete tmp;
		return;
	}
	if (root->right == NULL){
		NODE* tmp = root;
		root = root->left;
		delete tmp;
		return;
	}
	//Node has 2 children
	NODE* tmp = findMin(root->right);
	root->key = tmp->key;
	remove(root->right, tmp->key);
}
void removeTree(NODE* &pRoot)
{
	if (!pRoot)
		return;
	removeTree(pRoot->left);
	removeTree(pRoot->right);
	delete pRoot;
	pRoot = NULL;
}

int Height(NODE* pRoot)
{
	if (pRoot == NULL) return 0;
	int lheight = Height(pRoot->left);
	int rheight = Height(pRoot->right);
	if (lheight > rheight){
		return lheight + 1;
	}
	return rheight + 1;
	
}

int heightNode(NODE* pRoot, int value)
{
	if (pRoot == NULL) return 0;
	pRoot = Search(pRoot, value);
	if (pRoot){
		return Height(pRoot);
	}
	return - 1;
}
// Cau 15
int find(NODE *pRoot, NODE *p, int level) {
	if (pRoot == NULL)
		return 0;
	if (pRoot == p)
		return level;
	int x = find(pRoot->left, p, level + 1);
	if (x != 0)
		return x;
	x = find(pRoot->right, p, level + 1);
	return x;
}
int Level(NODE* pRoot, NODE* p) {
	if (pRoot == NULL)
		return 0;
	int level = 1;
	return find(pRoot, p, level);
}

int countLeaf(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (pRoot->left == NULL && pRoot->right == NULL)
		return 1;
	else
		return countLeaf(pRoot->left) + countLeaf(pRoot->right);
}

int countLess(NODE* root, int x) {
	if (root == NULL) return 0;
	int count = 0;
	if (x > root->key) {
		count++;
		count += countLess(root->left, x);
		count += countLess(root->right, x);
	}
	else count += countLess(root->left, x);
	return count;
}

bool checkTree(NODE* pRoot) {
	if (pRoot->left != NULL && pRoot->left->key > pRoot->key) return false;
	if (pRoot->right != NULL && pRoot->right->key < pRoot->key) return false;
	return pRoot->left == NULL ? 1 : checkTree(pRoot->left) && pRoot->right == NULL ? 1 : checkTree(pRoot->right);
}

bool isBST(NODE* pRoot) {
	if (pRoot == NULL) return true;
	if (pRoot->left != NULL) {
		NODE*pL = pRoot->left;
		while (pL->right != NULL) {
			pL = pL->right;
		}
		if (pL->key > pRoot->key) return false;
	} 
	if (pRoot->right != NULL) {
		NODE*pR = pRoot->right;
		while (pR->left != NULL) {
			pR = pR->left;
		}
		if (pR->key < pRoot->key) return false;
	}
	return checkTree(pRoot);
}

bool isFullBst(NODE* pRoot){
	if (isBST(pRoot) == false) return false;
	if (pRoot == NULL) return true;
	if (pRoot->left == NULL && pRoot->right == NULL) return true;
	if (pRoot->left && pRoot->right) return isFullBst(pRoot->left) && isFullBst(pRoot->right);
	return false;
}

int main(){
	NODE *pRoot = createNode(6);
	pRoot->left = createNode(4);
	pRoot->right = createNode(8);

	pRoot->left->left = createNode(3);
	pRoot->left->right = createNode(5);

	pRoot->right->left = createNode(7);
	pRoot->right->right = createNode(5);

	cout << isFullBst(pRoot);
	/*int a[9] = { 5, 8, 1, 2, 4, 6, 7, 3, 9 };
	NODE*p = createTree(a,9);*/
	//LNR(p);

	/*cout << Search(p, 8)->right->key;*/
	//LNR(p);
	//remove(p, 2);
	//cout << '\n';
	//removeTree(p);
	//LNR(p);

	//cout << "Height of Node " << heightNode(p, 1) << endl;

	//cout << "Leaf :" << countLeaf(p) << endl;
	//cout << "Level of node: " << Search(p, 8)->key << " is: " << Level(p, Search(p, 8)) << endl;
	//cout << "Nodes: " << countLess(p, 3) << endl;
	//cout << isBST(p) << endl;
	system("pause");
	return 0;
}