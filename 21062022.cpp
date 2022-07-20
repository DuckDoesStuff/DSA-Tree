#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct node{
	int key;
	node *left;
	node *right;
};
node* createNode(int data){
	node *p = new node;
	p->key = data;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void Insert(node* &pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	if (pRoot->key > x) 
		Insert(pRoot->left, x);
	else 
		Insert(pRoot->right, x);
}
void InsertLoop(node* &pRoot, int x){
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	node* p = pRoot;
	node* q = NULL;
	while (p != NULL){
		q = p;
		if (p->key == x) return;
		if (p->key > x) 
			p = p->left;
		else
			p = p->right;
	}

	if (q->key > x){
		q->left = createNode(x);
	}
	else q->right = createNode(x);
}

void NLR(node* pRoot) {
	if (pRoot == NULL)
		return;
	cout << pRoot->key << " ";
	NLR(pRoot->left);
	NLR(pRoot->right);
}

node* createTree(int a[], int n){
	node* T = NULL;
	for (int i = 0; i < n; ++i){
		InsertLoop(T, a[i]);
	}
	return T;
}

void LRN(node* pRoot){
	if (pRoot == NULL)
		return;
		LRN(pRoot->left);
		LRN(pRoot->right);
		cout << pRoot->key << " ";
}
void LNR(node* pRoot){
	if (pRoot == NULL)
		return;
	LNR(pRoot->left);
	cout << pRoot->key << " ";
	LNR(pRoot->right);
}

void levelOrder(node * pRoot) {
	queue <node *> q;
	node * curr;
	q.push(pRoot);
	while (!q.empty()) {
		curr = q.front();
		q.pop();
		if (curr->left != NULL) q.push(curr->left);
		if (curr->right != NULL) q.push(curr->right);
		cout << curr->key << " ";
	}
}

int Height(node* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}
	return 1 + max(Height(pRoot->left), Height(pRoot->right));
}

int countNode(node* pRoot)
{
	if (!pRoot)
		return 0;
	return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}

int sumNode(node* root){
	if (!root)
		return 0;
	return root->key + sumNode(root->left) + sumNode(root->right);
}

node* Search(node* root, int x) {
	if (root == NULL) return NULL;

	if (root->key == x) return root;
	if (x < root->key) return Search(root->left, x);
	else return Search(root->right, x);
}

int main(){
	node *pRoot = NULL;
	///*for (int i = 0; i < 10; i++) {
	//	Insert(pRoot, i);
	//}*/

	int a[] = { 1, 2, 3, 4, 10, 11, 22 };
	int n = 7;
	pRoot = createTree(a, n);
	////NLR(pRoot);
	levelOrder(pRoot);
	////LRN(pRoot);
	//LNR(pRoot);

	// cout << "Height : " << Height(pRoot) << endl;
	// cout << "Tree has " << countNode(pRoot) << " nodes" << endl;
	// cout << "Sum " << sumNode(pRoot) << endl;
	// cout << Search(pRoot, 11)->right->key << endl;
	// system("pause");
	return 0;
}