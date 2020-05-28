# include <iostream>
# include <vector>

using namespace std;

class TreeNode
{
public:
    int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        while(curr != nullptr){
            if(curr->val > p->val && curr->val > q->val) {
                curr = curr->left;
            } else if (curr->val < p->val && curr->val < q->val) {
                curr = curr->right;    
            } else {
                return curr;
            }
        }
        return nullptr;
    }

int main(){

    return 0;
}