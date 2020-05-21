import java.util.ArrayList;
class lec01{

    public static class node{
        int data;
        node left = null;   // node* left = null;
        node right = null;  // node* right = null;

        node(int data){
            this.data=data;
            this.left=this.right=null;
        }
    }

    static int idx = 0;

    public static node construct_Tree(int[] arr){
        if(idx==arr.length || arr[idx]==-1){
            idx++;
            return null;
        }

        node node = new node(arr[idx++]);
        node.left=construct_Tree(arr);
        node.right=construct_Tree(arr);
        
        return node;
    }

    public static void display_tree(node root){
        if(root==null){
            return;
        }
        String str="";
        str+=((root.left!=null)?root.left.data:".");
        str+= "<-"+root.data+"->";
        str+=((root.right!=null)?root.right.data:".");
        System.out.println(str);
        display_tree(root.left);
        display_tree(root.right);
    }

    public static void basic_tree(){
        int[] arr = {10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-170,110,-1,-1,120,-1,-1};
        node root = construct_Tree(arr);
        display_tree(root);
    }

// Basic_Question===========================================================
    
    public static int size(node root){
        if(root==null) return 0;
        return (size(root.left)+size(root.left)+1);
    }

    public static int height(node root){
        if(root==null) return -1;
        return Math.max(height(root.left),height(root.left))+1;
    }

    public static int max( node root ) {
        if( root == null )
            return (int)-1e8;
        int mymax = root.data;
        if( root.left != null )
            mymax = Math.max( mymax , max( root.left ) );
        if( root.right != null )
            mymax = Math.max( mymax , max( root.right ) );
        return mymax;
    }

    public static int min( node root ){
        if( root == null )
            return (int)1e8;
        int mymin = root.data;
        if( root.left != null )
            mymin = Math.min( mymin , min( root.left ) );
        if( root.right != null )
            mymin = Math.min( mymin , min( root.right ) );
        return mymin;
    }
    
    public static boolean find(node root,int data){
        if(root==null)return false;
        if(root.data==data)return true;
        return find(root.left,data) || find(root.right,data);
    }

    public static void basic_question(){
        int[] arr = {10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        node root = construct_Tree(arr);
        display_tree(root);
        System.out.println(size(root));
        System.out.println(height(root));
        System.out.println(max(root));
        System.out.println(min(root));
        System.out.println(find(root, 70));
    }

// tree triversal========================================================

    public static void preOrder( node root ){
        if( root == null ){
            return;
        }
        System.out.print( root.data+", ");
        if( root.left != null){
            preOrder( root.left );
        }
        if(root.right != null ){
            preOrder(root.right);
        }
    }
    public static void inOrder( node root ){
        if( root == null ){
            return;
        }
        if( root.left != null){
            inOrder( root.left );
        }
        System.out.print( root.data+", ");
        if(root.right != null ){
            inOrder(root.right);
        }
    }
    public static void postOrder( node root ){
        if( root == null ){
            return;
        }
        if( root.left != null){
            postOrder( root.left );
        }
        if(root.right != null ){
            postOrder(root.right);
        }
        System.out.print( root.data+", ");
    }

    public static void preOrderIterative( node root ) {
        ArrayList<node> stack = new ArrayList<>();
        stack.add(root);
        while(stack.size() > 0){
            node currNode = stack.remove( stack.size() - 1 );
            System.out.print(currNode.data+" ");
            if(currNode.right != null){
                stack.add(currNode.right);
            }
            if(currNode.left != null){
                stack.add(currNode.left);
            }
        }
    }

// rootToNodePath==========================================================================================

    public static boolean root_to_node_path(node root, int data,ArrayList<node> path){
        if(root==null) return false;
        if(root.data == data){
            path.add(root);
            return true;
        }
        boolean res = root_to_node_path(root.left, data, path) || root_to_node_path(root.right, data, path);
        if(res) path.add(root);
        return res;
    }

    public static ArrayList<node> root_to_node_path_ArrayList(node root,int data){
        if(root==null){
            return new ArrayList<>();
        }

        if(root.data==data){
           ArrayList<node> base = new ArrayList<>();
           base.add(root);
           return base; 
        }
        
        ArrayList<node> left = root_to_node_path_ArrayList(root.left, data);
        if(left.size()!=0){
            left.add(root);
            return left;
        }

        ArrayList<node> right = root_to_node_path_ArrayList(root.right, data);
        if(right.size()!=0){
            right.add(root);
            return right;
        }

        return new ArrayList<>();
    }

    public static void root_to_node_path_sol(){
        int[] arr = {10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        node root = construct_Tree(arr);
        
        ArrayList<node> path = new ArrayList<>();
        System.out.println(root_to_node_path(root, 90, path));   
        for(node n: path){
            System.out.print(n.data+"->");
        }

        System.out.println();
        System.out.println(root_to_node_path_ArrayList(root, 90));

    }

    public static void tree_triversal(){
        int[] arr = {10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        node root = construct_Tree(arr);

        display_tree(root);
        System.out.println();

        preOrder(root);
        System.out.println();

        inOrder(root);
        System.out.println();

        postOrder(root);
        System.out.println();

        preOrderIterative(root); 
        System.out.println();
    }

    public static void solve(){
        //basic_tree();
        //basic_question();
        //tree_triversal();
        root_to_node_path_sol();
    }

    public static void main(String[] args){
        solve();
    }

}