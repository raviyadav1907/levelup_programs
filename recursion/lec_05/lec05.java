// 7th may lecture

import java.util.Arrays;

class lec05{

    public static void main(String[] args) {
        solution();
    }

    public static void solution(){
        NQueens_problem();
        N_Knight_problem();
    }
    
    public static void NQueens_problem() {
        // boolean[][] rooms=new boolean[4][4];
        // int tnq = 4;

        //System.out.println(NQueens(rooms, 0, tnq, ""));
        //System.out.println(NQueen_Permutation(rooms,0, tnq, ""));
        //System.out.println(Nqueen_subseq_combination(rooms, 0, tnq, ""));
        //System.out.println(Nqueen_subseq_permutation(rooms, 0, tnq, ""));
    }

    public static void N_Knight_problem(){
        int[][] board=new int[8][8];
   
        for(int i=0;i<board.length;i++)
        Arrays.fill(board[i],-1);

        System.out.println(nKnight(board, 0, 0, 0));
    }

// Nqueen problem using combination======================================================================================================================================================

    public static boolean is_a_valid_location(boolean[][] rooms, int r, int c) {
        //direction for permutation
        int[][] direction = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
        //direction for combinaton
        //int[][] direction = {{0,-1},{-1,-1},{-1,0},{-1,1}};
        for(int d = 0 ; d<direction.length ; d++){
            for(int radius = 1 ; radius<=rooms.length ; radius++){
                int x = r + radius*direction[d][0];
                int y = c + radius*direction[d][1];
                if(x >= 0 && y >= 0 && x < rooms.length && y < rooms[0].length){
                        if(rooms[x][y]){
                            return false;
                        }
                }else break;
            }
        }
        return true;
    }

    public static int NQueens(boolean[][] rooms, int qpsf, int tnq, String ans) {
        if (tnq==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        for (int r = qpsf; r < rooms.length*rooms[0].length; r++){
            int x = r / rooms[0].length;
            int y = r % rooms[0].length;
            if(is_a_valid_location(rooms, x, y)){
                rooms[x][y]= true;
                count += NQueens(rooms, r + 1,tnq-1, ans + "(" + x + ", " + y + ") ");
                rooms[x][y]= false;
            }
        }
        return count;
    }

// NQueen problem using permutation====================================================================================================================================================

    public static int NQueen_Permutation(boolean[][] rooms,int index,int tnq, String ans) {
        if (tnq==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        for (int r = index; r < rooms.length*rooms[0].length; r++){
            int x = r / rooms[0].length;
            int y = r % rooms[0].length;

            if (!rooms[x][y] && is_a_valid_location(rooms, x, y))
            {
                rooms[x][y] = true;
                count += NQueen_Permutation(rooms,0,tnq-1,  ans + "(" + x + ", " + y + ") ");
                rooms[x][y] = false;
            }
        }
        return count;
    }

// NQueen problem subseq using combination====================================================================================================================================================
    public static int Nqueen_subseq_combination(boolean[][] board, int idx, int tnq, String ans){
        if (tnq==0 || idx==board.length*board[0].length)
        {
            if(tnq==0){
            System.out.println(ans);
            return 1;
            }
            return 0;
        }

        int count = 0;
        
        int x = idx / board[0].length;
        int y = idx % board[0].length;
        if(is_a_valid_location(board,x,y)){
            board[x][y]=true;
            count += Nqueen_subseq_combination(board, idx + 1,tnq-1, ans + "(" + x + ", " + y + ") ");
            board[x][y]=false;
        }
        count += Nqueen_subseq_combination(board, idx + 1,tnq, ans);
        return count;
    }
// NQueen problem subseq using permutation====================================================================================================================================================
    public static int Nqueen_subseq_permutation(boolean[][] board, int idx, int tnq, String ans){
        if (tnq==0 || idx==board.length*board[0].length)
        {
            if(tnq==0){
            System.out.println(ans);
            return 1;
            }
            return 0;
        }

        int count = 0;
        
        int x = idx / board[0].length;
        int y = idx % board[0].length;
        if(!board[x][y] && is_a_valid_location(board,x,y)){
            board[x][y]=true;
            count += Nqueen_subseq_permutation(board, 0,tnq-1, ans + "(" + x + ", " + y + ") ");
            board[x][y]=false;
        }
        count += Nqueen_subseq_permutation(board, idx + 1,tnq, ans);
        return count;
    }

// N_Knight problem =============================================================================================================================================================================
    public static boolean nKnight(int[][] board,int r,int c,int move){
        board[r][c]=move;
        if(move==63){ 
        for(int[] b: board){
            for(int ele: b) System.out.print(ele+ " ");
            System.out.println();
        }
        return true;
    }

    int[] xMove = {  2, 1, -1, -2, -2, -1,  1,  2 }; 
    int[] yMove = {  1, 2,  2,  1, -1, -2, -2, -1 };
    boolean res=false;

    for(int d=0;d<8;d++){
        int x = r + xMove[d];
        int y = c + yMove[d]; 

        if(x >= 0 && y >= 0 && x < 8 && y < 8 && board[x][y]==-1)
            res = res || nKnight(board , x , y , move+1);
        }

        board[r][c]=-1;

        return res;
    }

}
