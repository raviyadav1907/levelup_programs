import java.util.ArrayList;
class binary_tree{

    // node for tree 

    public static class Node{
        int data;
        Node left = null;   // node* left = null;
        Node right = null;  // node* right = null;

        Node(int data){
            this.data=data;
            this.left=this.right=null;
        }
    }

    // tree constructor

    static int idx = 0;

    public static Node construct_Tree(int[] arr){
        if(idx==arr.length || arr[idx]==-1){
            idx++;
            return null;
        }

        Node node = new Node(arr[idx++]);
        node.left=construct_Tree(arr);
        node.right=construct_Tree(arr);
        
        return node;
    }

    // tree display

    public static void display_tree(Node root){
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

    // rootToNodePath==========================================================================================
    
    public static boolean root_to_node_path(Node root, int data,ArrayList<Node> path){
        if(root==null) return false;
        if(root.data == data){
            path.add(root);
            return true;
        }
        boolean res = root_to_node_path(root.left, data, path) || root_to_node_path(root.right, data, path);
        if(res) path.add(root);
        return res;
    }


    public static ArrayList<Node> rootToNodePath_02(Node root,int data){
        
        if(root==null){
            return new ArrayList<>();
        }
        
        if(root.data==data){
            ArrayList<Node> base=new ArrayList<>();
            base.add(root);
            return base;
        }
  
        ArrayList<Node> left=rootToNodePath_02(root.left,data);
        if(left.size()!=0){
            left.add(root);
            return left;
        }
   
        ArrayList<Node> right=rootToNodePath_02(root.right,data);
        if(right.size()!=0){
            right.add(root);
            return right;
        }
        
        return new ArrayList<>();
      }

    public static void rootToNodePath(Node root,int data){
        ArrayList<Node> path=new ArrayList<>();
        root_to_node_path(root,data,path);
        for(Node n: path){
            System.out.print(n.data + " -> ");
        }
    }

   // Lowest_common_Ancestor_lowlevel========================================================================================================================================= 

    public Node lowestCommonAncestor(Node root, int p, int q) {
        ArrayList<Node> path1=new ArrayList<>();
        ArrayList<Node> path2=new ArrayList<>();
        
        root_to_node_path(root,p,path1);
        root_to_node_path(root,q,path2);

        Node prev=null;
        int i=path1.size()-1;
        int j=path2.size()-1;
        
        while(i>=0 && j>=0){
          if(path1.get(i).data!=path2.get(j).data) break;
          
          prev=path1.get(i);
          i--;
          j--;
        }

        return prev;
    }

    // Lowest_common_Ancestor_highlevel=========================================================================================================================================

    static Node LCAnode = null;

    public static boolean Lowest_Common_Ancestor(Node root,int p,int q){
        if(root==null)return false;

        boolean selfDone=false;

        if(root.data==p || root.data==q){
            selfDone=true;
        }

        boolean leftDone=Lowest_Common_Ancestor(root.left, p, q);
        if(LCAnode!=null)return true;

        boolean rightDone=Lowest_Common_Ancestor(root.right, p, q);
        if(LCAnode!=null)return true;

        if((selfDone && leftDone)||(selfDone && rightDone) ||(leftDone && rightDone))
            LCAnode=root;

        return selfDone||leftDone||rightDone;
    }

    // k near element ================================================================================================

    public static void kdown(Node root,int level,Node blocknode){
        if(root == null || root == blocknode)return;

        if(level==0){
            System.out.println(root.data+" ");
            return;
        }

        kdown(root.left, level-1, blocknode);
        kdown(root.right, level-1, blocknode);

    }

    public static void allnodekAway(Node root,int target,int k){
        ArrayList<Node> path = new ArrayList<>();
        root_to_node_path(root, target, path);

        Node blocknode = null;

        for(int i = 0 ; i<path.size() ; i++){
            if(k-i<0)break;
            kdown(path.get(i), k-1, blocknode);
            blocknode=path.get(i);
        }
    }


    public static void set1_tree(){
        int[] arr = {10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        Node root = construct_Tree(arr);
        display_tree(root);
        System.out.println(Lowest_Common_Ancestor(root, 90, 120));
        System.out.println("LCAnode : " + LCAnode.data);
    }

    public static void main(String[] args){
        set1_tree();
    }

}