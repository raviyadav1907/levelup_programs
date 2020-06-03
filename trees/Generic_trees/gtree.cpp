#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Node
{
public:
    int data;
    vector<Node*> childs;

    Node(int data)
    {
        this->data = data;
    }

    Node()
    {
    }
};

Node* gtree_Construct(vector<int>& arr){
    stack<Node*> current_parent_list;
    for(int i=0;arr.size()-1;i++){
        if(arr[i]!=-1){
            Node* curr_node = new Node(arr[i]);
            current_parent_list.push(curr_node);
        }else{
            Node* curr_node=current_parent_list.top();current_parent_list.pop();
            current_parent_list.top()->childs.push_back(curr_node);
        }
    }
    return current_parent_list.top();
}

void preorder(Node* node){
    cout << node->data + " ";
    for(Node* child:node->childs){
        preorder(child);
    }
}

void display(Node* node){
    string str = "";
    str+=(node->data + "->");
    for(Node* child: node->childs){
        str += child->data+" ";
    }
    cout<<str<<endl;
    for(Node* child: node->childs){
        display(child);
    }
}

void solve(){
    vector<int> arr = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100}; 
    Node* root = gtree_Construct(arr);
    display(root);
}

int main(){
    solve();
    return 0;
}