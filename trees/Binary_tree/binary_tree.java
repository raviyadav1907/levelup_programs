import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Stack;

import javax.swing.plaf.basic.BasicTreeUI.NodeDimensionsHandler;

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

    public static int height(Node root){
        if(root==null) return -1;
        return Math.max(height(root.left),height(root.left))+1;
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
            kdown(path.get(i), k-i, blocknode);
            blocknode=path.get(i);
        }
    }

    public static int allNodeAway_02(Node root,int target,int k){
        if(root==null)return -1;
        if(root.data == target){
            kdown(root,k, null);
            return 1;
        }
        int leftdistance=allNodeAway_02(root.left, target, k);
        if(leftdistance!=-1){
            if(k-leftdistance>=0) kdown(root, k-leftdistance, root.left);
            return leftdistance+1;
        }
        int rightdistance=allNodeAway_02(root.right, target, k);
        if(rightdistance!=-1){
            if(k-rightdistance>=0) kdown(root,k-rightdistance, root.right);
            return rightdistance+1;
        }
        return -1;
    }

    public static void kDown_1(Node root,int level){
        if(root==null) return;
 
        if(level==0){
          System.out.print(root.data + " ");
          return;  
        }
 
        kDown_1(root.left,level-1);
        kDown_1(root.right,level-1);
 
     }

    public static int allNodeAway_03(Node root,int target,int k){
        if(root==null) return -1;
        if(root.data==target){
            kdown(root, k, null);
            return 1;
        }
        int leftdistance = allNodeAway_03(root.left, target, k);
        if(leftdistance!=-1){
            if(k-leftdistance == 0)
                System.out.print(root.data+" ");
            else
                kDown_1(root.right, k-leftdistance-1);
            return leftdistance+1;
        }
        int rightdistance = allNodeAway_03(root.right, target, k);
        if(rightdistance!=-1){
            if(rightdistance == 0){
                System.out.print(root.data+" ");
            }else{
                kDown_1(root.left, k-rightdistance-1);
            return rightdistance+1;
            }
        }
        return -1;
    }
    
    // diameter of a tree =======================
    // copy tree height from tree basic=========================

    public static int diameter_01(Node node){
        if(node==null) return 0;
 
        int ld=diameter_01(node.left);
        int rd=diameter_01(node.right);
 
        int lh=height(node.left);
        int rh=height(node.right);
 
        int myDia = lh + rh + 2;
        return Math.max(Math.max(ld,rd), myDia);
    }

    public static class diaPair{
        int dia=0;
        int hei=0;
 
        diaPair(int dia,int hei){
            this.dia=dia;
            this.hei=hei;
        }
    }
 
    public static diaPair diameter_02(Node node){
     if(node==null) return new diaPair(0,-1) ;
 
     diaPair lr=diameter_02(node.left);  // left result
     diaPair rr=diameter_02(node.right); // right result
 
     diaPair myRes=new diaPair(0,-1);
     myRes.dia = Math.max(Math.max(lr.dia,rr.dia), (lr.hei+rr.hei+2));
     myRes.hei = Math.max(lr.hei,rr.hei)+1;
     
     return myRes;
    }
 
    static int diameter=0;
    public static int diameter_03(Node node){
        if(node==null) return -1 ;
    
        int lh = diameter_03(node.left); // left height
        int rh =diameter_03(node.right); // right height
        
        diameter=Math.max(diameter,lh+rh+2);
        return Math.max(lh,rh)+1;
    }

    public static void set1_tree(){
        int[] arr = {10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        Node root = construct_Tree(arr);
        display_tree(root);
        System.out.println(Lowest_Common_Ancestor(root, 90, 120));
        System.out.println("LCAnode : " + LCAnode.data);
    }

    //set2_tree=================================================================

    public static void levelOrder_00(Node node){
        LinkedList<Node> pQue = new LinkedList<>(); // addLast and removeFirst.
        pQue.addLast(node);

        while(pQue.size()!=0){
            Node rnode = pQue.removeFirst();
            System.out.print(rnode.data+" ");
            if(rnode.left!=null)pQue.addLast(rnode.left);
            if(rnode.right!=null)pQue.addLast(rnode.right);
        }

    }

    public static void levelOrder_01(Node node){
        LinkedList<Node> pQue = new LinkedList<>(); // addLast and removeFirst.
        LinkedList<Node> cQue = new LinkedList<>(); // addLast and removeFirst.   

        pQue.addLast(node);
        int count=0;
        System.out.print("Level : "+count+" ->");

        while(pQue.size()!=0){
            Node rnode = pQue.removeFirst();
            System.out.print(rnode.data+" ");
            if(rnode.left!=null) cQue.addLast(rnode.left);
            if(rnode.right!=null) cQue.addLast(rnode.right);

            if(pQue.size()==0){
                LinkedList<Node> temp = pQue;
                pQue=cQue;
                cQue=temp;
                count++;
                System.out.println("\nLevel : "+count+" ->");
            }
        }
    }

    public static void levelOrder_02(Node node){
        LinkedList<Node> Que = new LinkedList<>(); // addLast and removeFirst.     
        Que.addLast(node);
        Que.addLast(null);
        int count=0;
        System.out.print("Level : "+count+" ->");
        while(Que.size()!=0){
            Node rnode = Que.removeFirst();
            System.out.print(rnode.data+" ");
            if(rnode.left!=null) Que.addLast(rnode.left);
            if(rnode.right!=null) Que.addLast(rnode.right);

            if(Que.size()==0){
                Que.removeFirst();
                Que.addLast(null);
                count++;
                System.out.println("\nLevel : "+count+" ->");
            }
        }
    }

    public static void levelOrder_03(Node node){
        LinkedList<Node> pQue=new LinkedList<>(); // addLast and removeFirst.
        pQue.addLast(node);
        
        int count=0;
        while(pQue.size()!=0){
            System.out.print("Level: " + count + " -> ");
            count++;
            int size=pQue.size();
    
            while(size--> 0){
                Node rnode=pQue.removeFirst();
                System.out.print(rnode.data+ " ");
                if(rnode.left!=null) pQue.addLast(rnode.left);
                if(rnode.right!=null) pQue.addLast(rnode.right);    
            }
            System.out.println();
        }    
    }

    public static void leftView(Node node){
        LinkedList<Node> que=new LinkedList<>(); // addLast and removeFirst.
        que.addLast(node);
        while(que.size()!=0){
            int size=que.size();
            System.out.print(que.getFirst().data + " ");
            while(size--> 0){
                Node rnode=que.removeFirst();
                if(rnode.left!=null) que.addLast(rnode.left);
                if(rnode.right!=null) que.addLast(rnode.right);    
            }
        }
        System.out.println();
    } 

    public static void rightView(Node node){
        LinkedList<Node> que=new LinkedList<>(); // addLast and removeFirst.
        que.addLast(node);
        while(que.size()!=0){
            int size=que.size();
            Node prev=null;
            while(size--> 0){
                Node rnode=que.removeFirst();
                if(rnode.left!=null) que.addLast(rnode.left);
                if(rnode.right!=null) que.addLast(rnode.right);    
                prev=rnode;
            }
            System.out.print(prev.data + " ");
        }
        System.out.println();
    }
       static int leftMinValue=0;
       static int rightMaxValue=0;
    
       public static void width(Node node,int lev){
           if(node==null) return;
    
           leftMinValue=Math.min(leftMinValue,lev);
           rightMaxValue=Math.max(rightMaxValue,lev);
           
           width(node.left, lev - 1);
           width(node.right, lev + 1);
       } 
    
       public static class pairVO{
           Node node;  //actual Node
           int vl=0;  // vertical Level
           public pairVO(Node node,int vl){
               this.node=node;
               this.vl=vl;
           }
       }
    
       public static void verticalOrder(Node node){
           width(node,0);
           int n=rightMaxValue - leftMinValue + 1;
           ArrayList<ArrayList<Integer>> ans=new ArrayList<>(); // vector<vector<int>> (n,vector<int>());
           for(int i=0;i<n;i++)
             ans.add(new ArrayList<>());
          
    
           LinkedList<pairVO> que=new LinkedList<>();
           que.addLast(new pairVO(node,-leftMinValue));
    
           while(que.size()!=0){
               int size=que.size();
               while(size--> 0){
                   pairVO rpair=que.removeFirst();
                   ans.get(rpair.vl).add(rpair.node.data);
                   if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                   if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 1));    
               }
           }
    
           for(ArrayList<Integer> ar: ans)
              System.out.println(ar);
           System.out.println();
       }
    
       public static void verticalOrderSum(Node node){
        width(node,0);
        int[] ans=new int[rightMaxValue - leftMinValue + 1];
    
        LinkedList<pairVO> que=new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));
    
        while(que.size()!=0){
            int size=que.size();
            while(size--> 0){
                pairVO rpair=que.removeFirst();
                ans[rpair.vl] += rpair.node.data;
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 1));    
            }
        }
    
        for(int ar: ans)
           System.out.println(ar);
        System.out.println();
    }

    public static void Bottomview(Node node){
        width(node,0);
        int[] ans=new int[rightMaxValue - leftMinValue + 1];
        LinkedList<pairVO> que=new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));
    
        while(que.size()!=0){
            int size=que.size();
            while(size--> 0){
                pairVO rpair=que.removeFirst();

                ans[rpair.vl] = rpair.node.data;
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 1));    
            }
        }

        for(int ar: ans)
           System.out.println(ar);
        System.out.println();
    }

    public static void TopView(Node node){
        width(node,0);
        int[] ans = new int[rightMaxValue-leftMinValue+1];
        Arrays.fill(ans,(int)-1e8);
        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));

        while(que.size()!=0){
            int size=que.size();
            while(size--> 0){
                pairVO rpair=que.removeFirst();
                if(ans[rpair.vl] == (int)-1e8){
                    ans[rpair.vl] = rpair.node.data;
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 1));
                }    
            }
        }

        for(int ar: ans)
           System.out.println(ar);
        System.out.println();
    }

    static int leftDMinValue=0;
    public static void widthDiagonal(Node node,int lev){
        if(node==null) return;

        leftMinValue=Math.min(leftMinValue,lev);

        width(node.left, lev - 1);
        width(node.right, lev + 0);
    } 


    public static void diagonalOrder(Node node){
        widthDiagonal(node,0);
        int n= -leftDMinValue + 1;
        ArrayList<ArrayList<Integer>> ans=new ArrayList<>(); // vector<vector<int>> (n,vector<int>());
        for(int i=0;i<n;i++)
        ans.add(new ArrayList<>());
    

        LinkedList<pairVO> que=new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));

        while(que.size()!=0){
            int size=que.size();
            while(size--> 0){
                pairVO rpair=que.removeFirst();
                ans.get(rpair.vl).add(rpair.node.data);
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 0));    
            }
        }

        for(ArrayList<Integer> ar: ans)
        System.out.println(ar);
        System.out.println();
    }

    public static void diagonalSum(Node node){
        widthDiagonal(node,0);
        int n= -leftDMinValue + 1;
        int[] ans=new int[n];

        LinkedList<pairVO> que=new LinkedList<>();
        que.addLast(new pairVO(node,-leftMinValue));

        while(que.size()!=0){
            int size=que.size();
            while(size--> 0){
                pairVO rpair=que.removeFirst();
                ans[rpair.vl] += rpair.node.data;
                if(rpair.node.left!=null) que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if(rpair.node.right!=null) que.addLast(new pairVO(rpair.node.right,rpair.vl + 0));    
            }
        }

        for(int ele: ans)
        System.out.println(ele);
        System.out.println();
    }

    static Node DLLhead=null;
    static Node DLLprev=null;

    public static void DLL(Node node){
        if(node==null) return;
        
        DLL(node.left);
        
        if(DLLhead==null){
            DLLhead=node;
        }else{
            DLLprev.right=node;
            node.left=DLLprev;
        }
        DLLprev=node;

        DLL(node.right);
        
    }

    public static class allSolution{
        int height = 0;
        int size=0;
        boolean find=false;
 
        Node pred=null;
        Node succ=null;
        Node prev=null;
    }
 
    public static void allSol(Node node,int data,int level,allSolution pair){
     if(node==null) return;
     pair.size++;
     pair.height=Math.max(pair.height,level);
     pair.find= pair.find || node.data==data;
     
     if(node.data==data && pair.pred==null) pair.pred=prev;
     if(pair.prev!=null && pair.prev.data == data && pair.succ==null) pair.succ=node;
     pair.prev=node;
     
      allSol(node.left,data,level+1,pair);
      allSol(node.right,data,level+1,pair);
    }


    public static void set3(Node node){
        DLL(node);
        while(DLLhead!=null){
            System.out.print(DLLhead.data+ " ");
            DLLhead=DLLhead.right;
        }
    }

    //=================================================================

    public static class tpair{  //traversalPair
        Node node=null;
        boolean selfDone=false;
        boolean leftDone=false;
        boolean rightDone=false;

        tpair(Node node,boolean selfDone,boolean leftDone,boolean rightdone){
            this.node=node;
            this.leftDone=leftDone;
            this.selfDone=selfDone; 
            this.rightDone=rightDone;
        }
    }

    public static void ItrTraversalOfTree(Node node){
        Stack<tpair> st=new Stack<>();
        st.push(new tpair(node,false,false,false));
        
        while(st.size()!=0){
            if(st.peek().selfDone==false){
                st.peek().selfDone = true;
                System.out.print(st.peek().node.data+" ");
            }else if(st.peek().leftDone==false){
                st.peek().leftDone = true;
                if(st.peek().node.left!=null){
                    st.push(new tpair(st.peek().node.left,false,false,false));
                }
            }else if(st.peek().rightDone==false){
                st.peek().rightDone = true;
                if(st.peek().node.right!=null){
                    st.push(new tpair(st.peek().node.right,false,false,false));
                }
            }else {
                st.pop();
            }
        }
    }

    
    public static class tpair_{  //traversalPair
        Node node=null;
        boolean selfDone=false;
        boolean leftDone=false;
        boolean rightDone=false;
        
        int ld = -1;
        int rd = -1;
        int sd = -1;
        boolean isleft=false;

        tpair_(Node node,boolean selfDone,boolean leftDone,boolean rightDone,boolean isleft){
            this.node=node;
            this.leftDone=leftDone;
            this.selfDone=selfDone; 
            this.rightDone=rightDone;
            this.isleft=isleft;
        }
    }

    public static void ItrHeightOfTree(Node node){
        Stack<tpair_> st=new Stack<>();
        st.push(new tpair_(node,false,false,false,false));
        
        tpair_ rpair=null;
        while(st.size()!=0){
            if(st.peek().leftDone==false){
                st.peek().leftDone = true;
                if(st.peek().node.left!=null){
                    st.push(new tpair_(st.peek().node.left,false,false,false,true));
                }
            }else if(st.peek().rightDone==false){
                st.peek().rightDone = true;
                if(st.peek().node.right!=null){
                    st.push(new tpair_(st.peek().node.right,false,false,false,false));
                }
            }else if(st.peek().selfDone==false){
                st.peek().selfDone = true;
                st.peek().sd=Math.max(st.peek().ld,st.peek().rd)+1;
            }else {
                rpair=st.pop();
                if(st.size()!=0){
                    if(st.peek().isleft)
                        st.peek().ld=rpair.sd;
                    else 
                       st.peek().rd=rpair.sd;
                }
            }
        }

        System.out.println(rpair.sd);
    }

    public static Node rightMost_of_LeftNode(Node lnode,Node curr){
        while(lnode.right!=null && lnode.right!=curr){
            lnode=lnode.right;
        }
        return lnode;
    }


    public static void morrisInOrder(Node node){
        Node curr=node;
        while(curr!=null){
            if(curr.left==null){
                System.out.print(curr.data+" ");
                curr=curr.right;
            }else{
                Node leftNode=curr.left;
                Node rightMost=rightMost_of_LeftNode(leftNode,curr);
                if(rightMost.right==null){ // thread create
                   rightMost.right=curr;
                   curr=curr.left;
                }else{ // thread break
                    rightMost.right=null;
                    System.out.print(curr.data+" ");
                    curr=curr.right;
                }
            }
        }
        System.out.println();
    }

    public static void morrisPreOrder(Node node){
        Node curr=node;
        while(curr!=null){
            if(curr.left==null){
                System.out.print(curr.data+" ");
                curr=curr.right;
            }else{
                Node leftNode=curr.left;
                Node rightMost=rightMost_of_LeftNode(leftNode,curr);
                if(rightMost.right==null){ // thread create
                   rightMost.right=curr;
                   System.out.print(curr.data+" ");
                   curr=curr.left;
                }else{ // thread break
                    rightMost.right=null;
                    curr=curr.right;
                }
            }
        }
        System.out.println();
    }

    // psi = preStartIndex, pei=preEndIndex, isi=inStartIndex, iei=inEndIndex
    public static Node ConstructFromPreAndIn(int[] pre,int psi,int pei,int[] in,int isi,int iei){
        if(psi>pei || isi>iei) return null;

        Node node=new Node(pre[psi]);
        
        int idx=isi;
        while(in[idx]!=pre[psi]){
          idx++;
        }
        int tnel=idx-isi;  // total no of elements between isi and idx

        node.left=ConstructFromPreAndIn(pre,psi+1,psi+tnel,in,isi,idx-1);
        node.right=ConstructFromPreAndIn(pre,psi+tnel+1,pei,in,idx+1,iei);
        
        return  node;
      }

    public static Node ConstructFromPreAndIn(int[] pre, int[] in) {
        return ConstructFromPreAndIn(pre,0,pre.length-1,in,0,in.length-1);
    }

    
    // psi = postStartIndex, pei=postEndIndex, isi=inStartIndex, iei=inEndIndex
    public static Node ConstructFromPostAndIn(int[] post,int psi,int pei,int[] in,int isi,int iei){
        if(psi>pei || isi>iei) return null;

        Node node=new Node(pre[pei]);
        
        int idx=isi;
        while(in[idx]!=pre[psi]){
          idx++;
        }
        int tnel=idx-isi;  // total no of elements between isi and idx

        node.left=ConstructFromPostAndIn(post,psi,psi+tnel-1,in,isi,idx-1);
        node.right=ConstructFromPostAndIn(post,psi+tnel,pei-1,in,idx+1,iei);
        
        return  node;
    }

    public static Node ConstructFromPostAndIn(int[] post, int[] in) {
        return ConstructFromPostAndIn(post,0,post.length-1,in,0,in.length-1);
    }

    // psi = preStartIndex, pei=preEndIndex, ppsi=postStartIndex, ppei=postEndIndex
    public static Node ConstructFromPreAndPost(int[] post,int psi,int pei,int[] in,int ppsi,int ppei){
        if(psi>pei || ppsi>ppei) return null;
    
        Node node=new Node(pre[psi]);
            
        int idx=ppsi;
        while(post[idx]!=pre[psi+1]){
            idx++;
        }
        
        int tnel=idx-isi+1;  // total no of elements between isi and idx
    
        node.left=ConstructFromPreAndPost(post,psi+1,psi+tnel,in,ppsi,idx);
        node.right=ConstructFromPreAndPost(post,psi+tnel+1,pei,in,idx+1,iei-1);
            
        return  node;
    }
    
    public static Node ConstructFromPreAndPost(int[] pre, int[] post) {
        return ConstructFromPreAndPost(pre,0,pre.length-1,post,0,post.length-1);
    }


    public static void view(Node node){
        leftView(node);
        rightView(node);
        verticalOrder(node);
        verticalOrderSum(node);
        Bottomview(node);
        TopView(node);
        //diagonalOrder(node);
        //diagonalSum(node);
        morrisInOrder(node);
        morrisPreOrder(node);
    }
    

    public static void levelOrder(Node node){
        // levelOrder_00(node);
        // levelOrder_01(node);
        // levelOrder_02(node);
        //levelOrder_03(node);    
    }

    public static void set2_tree(){
        int[] arr={10,20,40,-1,-1,50,80,-1,-1,90,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
        Node root=construct_Tree(arr);
        display_tree(root);
        levelOrder(root);
        view(root);  
        set3(root);  
    }

    public static void main(String[] args){
        //set1_tree();
        set2_tree();
    }

}