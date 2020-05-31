#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int data;
    Node* left = nullptr;  // Node* left=nullptr;
    Node* right = nullptr; // Node* right=nullptr;

    int height = 0;
    int bal = 0;

    Node(int data)
    {
        this->data = data;
        this->height = 0;
        this->bal = 0;
    }

    Node()
    {
    }
};

int idx = 0;
Node *construct_BST(vector<int> &arr, int si, int ei)
{
    if (si > ei)
    {
        return nullptr; //NULL
    }
    int mid = (si+ei)>>1; // (si+ei)/2
    Node *node = new Node(arr[mid]); // Node* node=new Node(arr[idx++]);
    node->left = construct_BST(arr, si, mid-1);
    node->right = construct_BST(arr, mid+1, ei);

    return node;
}

// void display(Node *node)
// {
//     if (node == nullptr)
//         return;

//     string str = "";
//     str += ((node->left != nullptr) ? to_string(node->left->data) + "[" + to_string(node->left->bal)+","+to_string(node->left->height)+"]"  : ".");
//     str += " <- " + to_string(node->data) + " -> ";
//     str += ((node->right != nullptr) ? to_string(node->right->data) + "[" + to_string(node->left->bal)+","+to_string(node->left->height)+"]" : ".");
//     cout << (str) << endl;

//     display(node->left);
//     display(node->right);
// }

void display1(Node *node)
{
    if (node == nullptr)
        return;

    string str = "";
    str += ((node->left != nullptr) ? to_string(node->left->data) : ".");
    str += " <- " + to_string(node->data) + " -> ";
    str += ((node->right != nullptr) ? to_string(node->right->data) : ".");
    cout << (str) << endl;

    display1(node->left);
    display1(node->right);
}


int max_of_tree(Node* node){
    Node* curr = node;
    while(curr->right != nullptr){
        curr=curr->right;
    }
    return curr->data;
}

int min_of_tree(Node* node){
    Node* curr = node;
    while(curr->left != nullptr){
        curr=curr->left;
    }
    return curr->data;
}

// avl==========================================

void updatedHieghtBalance(Node* node){
    int lh = -1;
    int rh = -1;
    if(node->left != nullptr)
        lh = node->left->height;
    if(node->right != nullptr)
        rh = node->left->height;
    node->height = max(lh,rh)+1;
    node->bal = lh - rh;
}

Node* ll(Node* x){
    Node* y = x->left;
    Node* ykaRight = y->right;

    y->right = x;
    x->left = ykaRight;

    updatedHieghtBalance(x);
    updatedHieghtBalance(y);

    return y;
}

Node* rr(Node* x){
    Node* y = x->right;
    Node* ykaLeft = y->left;

    y->left = x;
    x->right = ykaLeft;

    updatedHieghtBalance(x);
    updatedHieghtBalance(y);

    return y;
}

Node* getRotation(Node* node){
    updatedHieghtBalance(node);
    if(node->bal == 2){//ll,lr
        if(node->left->bal ==1){//ll
            return ll(node);
        }else{//lr
            node->left = rr(node->left);
            return ll(node);
        }
    }else if(node->bal == -2){//rr,rl
        if(node->right->bal == -1){ //rr
            return rr(node);
        }else{//rl
            node->right = ll(node->right);
            return rr(node);
        }
    }
    return node;
}

Node *addData(Node *root, int data)
{
    if (root == nullptr)
        return new Node(data);
    if (data < root->data)
        root->left = addData(root->left, data);
    else
        root->right = addData(root->right, data);

    root = getRotation(root);
    return root;
}

Node *removeData(Node *root, int data)
{
    if (root == nullptr)
        return nullptr;  // never found data;
    
    if (data < root->data)
        root->left = removeData(root->left, data);
    else if(data > root->data)
        root->right = removeData(root->right, data);
    else{  // data found.
      
        if(root->left == nullptr || root->right == nullptr) 
            return root->left!=nullptr?root->left:root->right;
       
       int maxInleft=max_of_tree(root->left);
       root->data=maxInleft;
       root->left=removeData(root->left,maxInleft);
    
    }
    root = getRotation(root);
    return root;
}

void solve(Node* root){
    for(int i = 1 ; 1<12 ; i++){
        root = addData(root,i*10);
    }
    display1(root);
}

int main(){
    Node* root = nullptr;
    solve(root);
    return 0;
}