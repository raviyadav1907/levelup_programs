//8th may;

import java.util.*;

class lec06{

    public static void main(String[] args){
        solution();
    }

    public static void solution(){
        //Nqueen_optimitation();
        Nqueen_optimitation_bits();
    }

    public static void Nqueen_optimitation(){
        int tnq = 4 ;
        int n = 4 ;
        int m = 4 ;
        row = new boolean[n];
        col = new boolean[m];
        diag = new boolean[n+m-1];
        antidiag = new boolean[m+n-1];
        System.out.println(Nqueen_Optimized(n, m, 0, tnq, ""));
    }

    public static void Nqueen_optimitation_bits(){
        int tnq = 12 ;
        int n = 12 ;
        int m = 12 ;
        System.out.println(Nqueen_Optimized_bits(n, m, 0, tnq, ""));
    }

// NQueen Optimized=====================================================================================================================================================

    public static boolean[] row;
    public static boolean[] col;
    public static boolean[] diag;
    public static boolean[] antidiag;

    public static int Nqueen_Optimized(int n, int m, int idx, int tnq, String ans){
        if(tnq==0){
            System.out.println(ans);
            return 1;
        }
        int count = 0;
        for (int i = idx; i < n*m ; i++){
            int x = i / m;
            int y = i % m;
            if(!row[x] && !col[y] && !diag[x+y] && !antidiag[x-y+(m-1)]){
                row[x]=true;
                col[y]=true;
                diag[x+y]=true;
                antidiag[x-y+m-1]=true;
                count += Nqueen_Optimized(n,m, i+1,tnq-1, ans + "(" + x + ", " + y + ") ");
                row[x]=false;
                col[y]=false;
                diag[x+y]=false;
                antidiag[x-y+m-1]=false;
            }
        }
        return count;
    }

// Nqueen using Bitmasking==============================================================================================================================================

    public static int row_bit = 0;
    public static int col_bit = 0;
    public static int diag_bit = 0;
    public static int antidiag_bit = 0;

    public static int Nqueen_Optimized_bits(int n, int m, int idx, int tnq, String ans){
        if(tnq==0){
            System.out.println(ans);
            return 1;
        }
        int count = 0;
        for (int i = idx; i < n*m ; i++){
            int x = i / m;
            int y = i % m;
            if((row_bit &(1<<x))==0 && (col_bit &(1<<y))==0 && (diag_bit &(1<<(x+y)))==0 && (antidiag_bit&(1<<(x-y+m-1)))==0){
                row_bit^=(1<<x);
                col_bit^=(1<<y);
                diag_bit^=(1<<(x+y));
                antidiag_bit^=(1<<(x-y+m-1));
                count += Nqueen_Optimized_bits(n,m, i+1,tnq-1, ans + "(" + x + ", " + y + ") ");
                row_bit^=(1<<x);
                col_bit^=(1<<y);
                diag_bit^=(1<<(x+y));
                antidiag_bit^=(1<<(x-y+m-1));
            }
        }
        return count;
    }

}