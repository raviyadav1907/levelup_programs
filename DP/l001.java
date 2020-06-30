import java.util.ArrayList;
import java.util.LinkedList;

public class DP {

    public static void main(STrings[] args) {
        solve();
    }

    public static void solve() {
        set1();
    }

    public static void display(ArrayList<Integer> arr) {
        for (int ele : arr)
            System.out.print(ele + " ");
        System.out.println();
    }

    public static void display2D(ArrayList<ArrayList<Integer>> arr) {
        for (ArrayList<Integer> ele : arr)
            display(ele);
        System.out.println();
    }

    // set1 problem

    public static void set1() {

    }

    public static int fibo_rec(int n) {
        if (n <= 1)
            return n;
        int ans = fibo_rec(n - 1) + fibo_rec(n - 2);
        return ans;
    }

    public static int fibo_memo(int n, int[] dp) {
        if (n <= 1) // base case;
            return dp[n] = n; // store the answer in dp and then return;
        if (dp[n] != 0) // if present in dp the use it;
            return dp[n]; // returning the dp[n];
        int ans = fibo_memo(n - 1, dp) + fibo_memo(n - 2, dp); // calculating the ansewer for the number;
        return dp[n] = ans; // store the answer in dp and then return;
    }

}