#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* p = new Node;
    p->key=data;
    p->left=NULL;
    p->right=NULL;
    return p;
}

Node* findMax(Node* pRoot) {
    while(pRoot->right!=NULL) {
        pRoot=pRoot->right;
    }
    return pRoot;
}
//AVL tree
int height(Node* pRoot) {
    if (pRoot==NULL) return 0;

    int heightL= height(pRoot->left);
    int heightR= height(pRoot->right);

    return max(heightL, heightR)+1;
}


void LR(Node* &pRoot) {
    Node* p= pRoot->right;
    pRoot->right=p->left;
    p->left=pRoot;
    pRoot=p;
}

void RR(Node* &pRoot) {
    Node* p=pRoot->left;
    pRoot->left=p->right;
    p->right=pRoot;
    pRoot=p;
}

void Insert(Node* &pRoot, int x) {
    if (pRoot==NULL) {
        pRoot=createNode(x);
        return;
    }
    if (pRoot->key==x) {
        return;
    }
    if (pRoot->key<x) {
        Insert(pRoot->right, x);
    }
    else {
        Insert(pRoot->left, x);
    }
}

void Balance(Node* &pRoot) {
    int h=height(pRoot->left)-height(pRoot->right);
    if (h>=2) {
        if (height(pRoot->left->left)>height(pRoot->left->right)) {
            LR(pRoot);
        }
        if (height(pRoot->left->left)<height(pRoot->left->right)) {
            LR(pRoot->left);
            RR(pRoot);
        }
    }
    if (h<=-2) {
        if (height(pRoot->right->right)>height(pRoot->right->left)) {
            LR(pRoot);
        }
        if (height(pRoot->right->right)<height(pRoot->right->left)) {
            RR(pRoot->right);
            LR(pRoot);
        }
    }
}

void InsertAVL(Node* &pRoot, int data) {
    if (pRoot==NULL) {
        pRoot=createNode(data);
    }

    if(pRoot->key>data) {
        Insert(pRoot->left, data);
    }
    if (pRoot->key<data) {
        Insert(pRoot->right, data);
    }
    Balance(pRoot);
}

void Remove(Node* &pRoot, int data) {
    if (pRoot==NULL) {
        return;
    }
    else if (pRoot->key>data) {
        Remove(pRoot->left, data);
    }
    else if (pRoot->key<data) {
        Remove(pRoot->right, data);
    }
    else if (pRoot->key==data) {
        if (pRoot->left==NULL && pRoot->right==NULL) {
            delete pRoot;
            pRoot==NULL;
            return;
        }

        else if (pRoot->left==NULL && pRoot->right!=NULL) {
            Node* p=pRoot;
            pRoot=pRoot->right;
            delete p;
        }
        else if (pRoot->left!=NULL && pRoot->right==NULL) {
            Node* p=pRoot;
            pRoot=pRoot->left;
            delete p;
        }
        else if (pRoot!=NULL && pRoot->right!=NULL) {
            Node* p=pRoot->left;
            pRoot->key=p->key;
            Remove(pRoot->right, pRoot->key);
        }
    }
    if (pRoot) Balance(pRoot);
}

Node* createTree(vector <int> a, int n) {
    Node* T =NULL;
    for (int i=0; i<n; ++i) {
        InsertAVL(T, a[i]);
    }
    return T;
}

// vector <int> Input(ifstream &fin) {
//     string s;
//     vector <int> a;

//     while(!fin.eof()) {
//         getline(fin, s, ',');
//         a.push_back(stoi(s));
//     }
//     return a;
// }

int countNode(Node* pRoot) {
    if (pRoot==NULL) return 0;
    return 1+countNode(pRoot->left)+countNode(pRoot->right);
}

// Node* findMax(Node* pRoot) {
//     while(pRoot->right!=NULL) {
//         pRoot=pRoot->right;
//     }
//     return pRoot;
// }

Node* findMin(Node* pRoot) {
    while (pRoot->left!=NULL) {
        pRoot=pRoot->left;
    }
    return pRoot;
}
Node* Search(Node* pRoot, int x) {
    if (pRoot==NULL || pRoot->key==x) return pRoot;
    else if (pRoot->key>x) return Search(pRoot->left, x);
    else return Search(pRoot->right, x);
}

void remove(Node* &pRoot, int x) {
    if (pRoot==NULL) return;
    else if (pRoot->key>x) {
        remove(pRoot->left, x);
    }
    else if (pRoot->key<x) {
        remove(pRoot->right, x);
    }
    else {
        if (pRoot->left==NULL && pRoot->right==NULL) {
            delete pRoot;
            pRoot = NULL;
        }
        else if (pRoot->left!=NULL && pRoot->right!=NULL) {
            Node* max = findMax(pRoot->left);
            pRoot->key= max->key;
            remove(pRoot->left, max->key);
        }
        else {
            Node* child= pRoot->left?pRoot->left:pRoot->right;
            Node* temp=pRoot;
            pRoot = child;
            delete temp;
        }
    }
}

int find(Node* pRoot, Node* cur, int level) {
    if (pRoot==NULL) return 0;
    if (pRoot==cur) return level;

    int x=find(pRoot->left, cur, level+1);
    if (x!=0) return x;
    else x=find(pRoot->right, cur, level+1);
    return x;
}

int level(Node* pRoot, Node* cur) {
    if (pRoot==NULL) return 0;
    int level=1;
    return find(pRoot, cur,level);
}


int heightNode(Node* pRoot, int x) {
    if (pRoot==NULL) return 0;

    Node* cur = Search(pRoot, x);
    return height(cur);
}

int countLeaf(Node* pRoot) {
    if (pRoot==NULL) return 1;
    if (pRoot->left == NULL && pRoot->right==NULL) return 1;
    else return countLeaf(pRoot->left)+countLeaf(pRoot->right);
}

int countLess(Node* pRoot, int x) {
    if (pRoot==NULL) return 0;
    int count=0;

    if (pRoot->key<x) {
        count++;
        count=count+countLess(pRoot->left, x);
        count=count+countLess(pRoot->right, x);
    }
    else {
        count= count+countLess(pRoot->left,x);
    }
    return count;
}

int countGreater(Node* pRoot, int x) {
    if (pRoot==NULL) return 0;
    int count=0;
    if (pRoot->key>x) {
        count++;
        count=count+countGreater(pRoot->left, x);
        count=count+countGreater(pRoot->right, x);
    }
    else {
        count=count+countGreater(pRoot->right, x);
    }
    return count;
}

void LNR(Node* pRoot) {
    if (pRoot==NULL) return;
    LNR(pRoot->left);
    cout << pRoot->key <<"\t";
    LNR(pRoot->right);
}

bool checkTree(Node* pRoot) {
    if (pRoot->left!=NULL && pRoot->left->key>pRoot->key) return false;
    if (pRoot->right!=NULL && pRoot->right->key<pRoot->key) return false;

    return pRoot->left==NULL? true:checkTree(pRoot->left) &&
            pRoot->right==NULL? true:checkTree(pRoot->right);
}

bool isBST (Node* pRoot) {
    if (pRoot==NULL) return true;
    if (pRoot->left!=NULL) {
        Node* maxLeft=findMax(pRoot->left);
        if (maxLeft->key>pRoot->key) return false;
    }
    if (pRoot->right!=NULL) {
        Node* minRight=findMin(pRoot->right);
        if (minRight->key<pRoot->key) return false;
    }
    return checkTree(pRoot);
}

bool isFullBST(Node* pRoot) {
    if (!isBST(pRoot)) return false;
    if (pRoot->left==NULL && pRoot->right==NULL) return true;
    else if (pRoot->left!=NULL && pRoot->right!=NULL) {
        return isFullBST(pRoot->left) && isFullBST(pRoot->right);
    }
    return false;
}

bool identicalTree(Node* pRoot1, Node* pRoot2) {
    if (pRoot1==NULL && pRoot2==NULL) return true;
    else if (pRoot1!=NULL && pRoot2!=NULL) {
        return identicalTree(pRoot1->left, pRoot2->left) &&
            identicalTree(pRoot1->right, pRoot2->right);
    }
    return false;
}

//AVL tree




int main () {
    Node* T1;
    Node* T2;
    vector <int> a =  {1, 2, 3, -1, -5, 10};
    //vector <int> b = {2, 3, 4, 5};

    ifstream fin;
    fin.open("input1.txt");

    //a=Input(fin);
    T1=createTree(a, a.size());
    //T2=createTree(b, b.size());

    //cout << identicalTree(T1, T2);


    // //remove(T, -5);
    LNR(T1); 
    // cout<< endl;
    // cout << countNode(T);
    
    // Node* search;
    // search = Search(T, 12);

    // cout << endl;
    // cout << search->left->key;
    // cout <<endl;
    // cout << height(T);

    fin.close();

    return 0;
}