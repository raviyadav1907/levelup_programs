#include <iostream>
#include <vector>
#include <list>

using namespace std;

void display(vector<int> &arr)
{
    for (int ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<int>> &arr)
{
    for (vector<int> ar : arr)
        display(ar);
    cout << endl;
}

int fibo(int n)
{
    if (n <= 1)
        return n;
    int ans = fibo(n - 1) + fibo(n - 2);
    return ans;
}

int fibo_memo(int n, vector<int> dp)
{
    if (n <= 1)                                            //base case;
        return dp[n] = n;                                  // store the answer in dp and then return;
    if (dp[n] != 0)                                        //if present in dp the use it;
        return dp[n];                                      // returning the dp[n];
    int ans = fibo_memo(n - 1, dp) + fibo_memo(n - 2, dp); //calculating the ansewer for the number;
    return dp[n] = ans;                                    // store the answer in dp and then return;
}

int fibo_dp(int N, vector<int> dp)
{
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = n;
            continue;
        }
        int ans = dp[n - 1] + dp[n - 2];

        dp[n] = n;
    }
    return dp[N];
}

int fibo_btr(int n)
{
    int a = 0;
    int b = 1;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return a;
}

//MazeiathSeries.==============================================

int mazeiathHV(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    if (sr + 1 <= er)
        count += mazeiathHV(sr + 1, sc, er, ec, dp);

    if (sc + 1 <= ec)
        count += mazeiathHV(sr, sc + 1, er, ec, dp);

    if (sr + 1 <= er && sc + 1 <= ec)
        count += mazeiathHV(sr + 1, sc + 1, er, ec, dp);

    return dp[sr][sc] = count;
}

int mazeiathHV_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{

    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if (sr + 1 <= er)
                count += dp[sr + 1][sc]; //mazeiathHV(sr + 1, sc, er, ec, dp);

            if (sc + 1 <= ec)
                count += dp[sr][sc + 1]; //mazeiathHV(sr, sc + 1, er, ec, dp);

            if (sr + 1 <= er && sc + 1 <= ec)
                count += dp[sr + 1][sc + 1]; //mazeiathHV(sr + 1, sc + 1, er, ec, dp);

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int mazeiath_memo_njumps(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    int count = 0;

    if (dp[sr][sc] != 0)
        return dp[sr][sc];
    for (int jump = 1; sr + jump <= er; jump++)
    {
        count += mazeiath_memo_njumps(sr + jump, sc, er, ec, dp);
    }
    for (int jump = 1; sc + jump <= ec; jump++)
    {
        count += mazeiath_memo_njumps(sr, sc + jump, er, ec, dp);
    }
    for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
    {
        count += mazeiath_memo_njumps(sr + jump, sc + jump, er, ec, dp);
    }
    return dp[sr][sc] = count;
}

int mazeiath_tabu_njumps(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }
            int count = 0;
            for (int jump = 1; sr + jump <= er; jump++)
            {
                count += dp[sr + jump][sc]; //mazeiath_memo_njumps(sr+n,sc,er,ec,dp);
            }
            for (int jump = 1; sc + jump <= ec; jump++)
            {
                count += dp[sr][sc + jump]; //mazeiath_memo_njumps(sr,sc+n,er,ec,dp);
            }
            for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
            {
                count += dp[sr + jump][sc + jump]; //mazeiath_memo_njumps(sr+n,sc+n,er,ec,dp);
            }
            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int dice_arr_memo(int si, int ei, vector<int> &dp)
{
    if (si == ei)
        return dp[si] = 1;
    int count = 0;
    if (dp[si] != 0)
        return dp[si];
    for (int jump = 1; si + jump <= ei && jump <= 6; jump++)
    {
        count += dp[si + jump]; //dice_arr(si+jump,ei,dp);
    }
    return dp[si] = count;
}

int dice_arr_tabu(int si, int ei, vector<int> &dp)
{
    for (int si = ei; si >= 0; si--)
    {
        if (si == ei)
        {
            dp[si] = 1;
            continue;
        }
        int count = 0;
        for (int jump = 1; si + jump <= ei && jump <= 6; jump++)
        {
            count += dp[si + jump]; //dice_arr(si+jump,ei,dp);
        }
        dp[si] = count;
    }
    return dp[0];
}

int dice_arr_best(int si, int ei)
{
    list<int> ll;
    for (si = ei; si >= 0; si--)
    {
        if (si > ei - 2)
        {
            ll.push_front(1);
            continue;
        }

        if (ll.size() <= 6)
            ll.push_front(2 * ll.front());
        else
        {
            ll.push_front(2 * ll.front() - ll.back());
            ll.pop_back();
        }
    }

    return ll.front();
}

int dice_arr_givearr(int si, int ei, vector<int> &dp, vector<int> diceArr)
{
    for (si = ei; si >= 0; si--)
    {
        if (si == ei)
        {
            dp[si] = 1;
            continue;
        }

        int count = 0;
        for (int dice = 0; si + diceArr[dice] <= ei && dice < diceArr.size(); dice++)
            count += dp[si + diceArr[dice]]; //boardPath(si + dice, ei, dp);
        dp[si] = count;
    }

    return dp[0];
}

//Leetcode 70.=================================================================================

int climbStairs_01(int n, vector<int> &dp)
{
    if (n <= 1)
    {
        return dp[n] = 1;
    }

    if (dp[n] != 0)
        return dp[n];

    int ans = climbStairs_01(n - 1, dp) + climbStairs_01(n - 2, dp);
    return dp[n] = ans;
}

int climbStairs_DP(int n, vector<int> &dp)
{
    int N = n;
    for (n = 0; n <= N; n++)
    {

        if (n <= 1)
        {
            dp[n] = 1;
            continue;
        }

        int ans = dp[n - 1] + dp[n - 2]; //climbStairs_01(n - 1, dp) + climbStairs_01(n - 2, dp);
        dp[n] = ans;
    }
    return dp[N];
}

int climbStairs_btr(int n)
{
    int a = 1;
    int b = 1;
    int sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}

// leetcode 476 ===================================================================================

int minCostClimbingStairs(int n, vector<int> &dp, vector<int> &cost)
{
    if (n <= 1)
    {
        return dp[n] = cost[n];
    }

    if (dp[n] != 0)
        return dp[n];

    int ans = min(minCostClimbingStairs(n - 1, dp, cost),
                  minCostClimbingStairs(n - 2, dp, cost));
    return dp[n] = ans + cost[n];
}

int minCostClimbingStairsDP(int n, vector<int> &dp, vector<int> &cost)
{
    int N = n;
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = cost[n];
            continue;
        }

        int ans = min(dp[n - 1], dp[n - 2]);
        dp[n] = ans + cost[n];
    }
    return dp[N];
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();

    cost.push_back(0);
    vector<int> dp(n + 1, 0);

    // return minCostClimbingStairs(n, dp, cost);
    return minCostClimbingStairsDP(n, dp, cost);
}

int climbStairs(int n)
{
    vector<int> dp(n + 1, 0);
    // return climbStairs_01(n, dp);
    // return climbStairs_DP(n,dp);
    return climbStairs_btr(n);
}

// friend_pairing_problem =========================================================================

int friend_pairing_problem_rec(int n, vector<int> &dp)
{
    if (n <= 1)
        return 1;

    int single = friend_pairing_problem_rec(n - 1, dp);
    int pair = friend_pairing_problem_rec(n - 2, dp) * (n - 1);

    return (single + pair);
}

int friend_pairing_problem_memo(int n, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = 1;
    if (dp[n] != 0)
        return dp[n];
    int single = friend_pairing_problem_memo(n - 1, dp);
    int pair = friend_pairing_problem_memo(n - 2, dp) * (n - 1);
    return dp[n] = (single + pair);
}

int friend_pairing_problem_tabu(int n, vector<int> &dp)
{
    int N = n;
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = 1;
            continue;
        }
        int single = dp[n - 1];         //friend_pairing_problem_memo(n-1,dp);
        int pair = dp[n - 2] * (n - 1); //friend_pairing_problem_memo(n-2,dp)*(n-1);
        dp[n] = (single + pair);
    }
    return dp[n];
}

void gfg_friend_pair_prob()
{
    int n = 10;
    vector<int> dp(n + 1);
    cout << friend_pairing_problem_rec(n, dp) << endl;
    cout << friend_pairing_problem_memo(n, dp) << endl;
    cout << friend_pairing_problem_tabu(n, dp) << endl;
}

// leetcode 64 ================================================================================

int minpathsum_rec(int row, int col, vector<vector<int>> &dp)
{
}

int minpathsum_memo(int row, int col, vector<vector<int>> &dp)
{
}

int minpathsum_tabu(int row, int col, vector<vector<int>> &dp)
{
}

int minPathSum(vector<vector<int>> &grid)
{
    int row = grid.size();
    int col = grid[0].size();
    //return minpathsum_rec(row, col, grid);
    // return minpathsum_memo(row, col, grid);
    // return minpathsum_tabu(row, col, grid);
}

// gfg goldmine_problem ==========================================================

int getMaxGold(vector<vector<int>> gold, int m, int n)
{
    int goldTable[m][n];

    for (int col = n - 1; col >= 0; col--)
    {
        for (int row = 0; row < m; row++)
        {
            int right = (col == n - 1) ? 0 : goldTable[row][col + 1];

            int right_up = (row == 0 || col == n - 1) ? 0 : goldTable[row - 1][col + 1];

            int right_down = (row == m - 1 || col == n - 1) ? 0 : goldTable[row + 1][col + 1];

            goldTable[row][col] = gold[row][col] +
                                  max(right, max(right_up, right_down));
        }
    }

    int res = goldTable[0][0];
    for (int i = 1; i < m; i++)
        res = max(res, goldTable[i][0]);
    return res;
}

void gfg_gold()
{
    vector<vector<int>> gold = {{1, 3, 1, 5},
                    {2, 2, 4, 1},
                    {5, 0, 2, 3},
                    {0, 6, 1, 2}};
    int m = 4, n = 4;
    cout << getMaxGold(gold, m, n);
}

void set1()
{
    int n, m;
    n = 3;
    m = 3;
    vector<vector<int>> dp(n, vector<int>(m));
    cout << mazeiath_memo_njumps(0, 0, n - 1, m - 1, dp);
}

void solve()
{
    //set1();
    gfg_friend_pair_prob();
}

int main()
{
    solve();
    return 0;
}