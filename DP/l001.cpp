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

int minPathSum(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (sr == grid.size() - 1 && sc == grid[0].size() - 1)
    {
        return dp[sr][sc] = grid[sr][sc];
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int minCost = 1e8;
    if (sr + 1 < grid.size())
        minCost = min(minCost, minPathSum(sr + 1, sc, grid, dp));
    if (sc + 1 < grid[0].size())
        minCost = min(minCost, minPathSum(sr, sc + 1, grid, dp));

    return dp[sr][sc] = minCost + grid[sr][sc];
}

int minPathSum_DP(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    for (sr = grid.size() - 1; sr >= 0; sr--)
    {
        for (sc = grid[0].size() - 1; sc >= 0; sc--)
        {

            if (sr == grid.size() - 1 && sc == grid[0].size() - 1)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int minCost = 1e8;
            if (sr + 1 < grid.size())
                minCost = min(minCost, dp[sr + 1][sc]);
            if (sc + 1 < grid[0].size())
                minCost = min(minCost, dp[sr][sc + 1]);

            dp[sr][sc] = minCost + grid[sr][sc];
        }
    }
    return dp[0][0];
}

int minPathSum(vector<vector<int>> &grid)
{
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
    return minPathSum(0, 0, grid, dp);
}

// gfg goldmine_problem ==========================================================

int goldMin(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    if (sc == grid[0].size() - 1)
    {
        return dp[sr][sc] = grid[sr][sc];
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};
    int maxCoins = 0;
    for (int d = 0; d < 3; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];
        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size())
        {
            maxCoins = max(maxCoins, goldMin(x, y, grid, dp));
        }
    }

    return dp[sr][sc] = maxCoins + grid[sr][sc];
}

int goldMin_DP(vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    for (int sc = grid[0].size() - 1; sc >= 0; sc--)
    {
        for (int sr = grid.size() - 1; sr >= 0; sr--)
        {
            if (sc == grid[0].size() - 1)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};
            int maxCoins = 0;
            for (int d = 0; d < 3; d++)
            {
                int x = sr + dir[d][0];
                int y = sc + dir[d][1];
                if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size())
                    maxCoins = max(maxCoins, dp[x][y]);
            }

            dp[sr][sc] = maxCoins + grid[sr][sc];
        }
    }

    int maxCoin = 0;
    for (int i = 0; i < grid.size(); i++)
        maxCoin = max(maxCoin, dp[i][0]);
    return maxCoin;
}

void gfg_gold()
{
    vector<vector<int>> gold = {{1, 3, 1, 5},
                                {2, 2, 4, 1},
                                {5, 0, 2, 3},
                                {0, 6, 1, 2}};
    int m = 4, n = 4;
}

// https://www.geeksforgeeks.org/count-number-of-ways-to-partition-a-set-into-k-subsets/

int count_of_ways(int n, int k, vector<vector<int>> &dp)
{
    if (n < k)
        return 0;
    if (n == k || k == 1)
        return dp[k][n] = 1;

    if (dp[k][n] != 0)
        return dp[k][n];

    int newGroup = count_of_ways(n - 1, k - 1, dp);
    int ExistingGroup = count_of_ways(n - 1, k, dp) * k;

    return dp[k][n] = newGroup + ExistingGroup;
}

int count_of_ways_DP(int n, int k, vector<vector<int>> &dp)
{

    int K = k, N = n;
    for (k = 1; k <= K; k++)
    {
        for (n = 0; n <= N; n++)
        {
            if (n < k)
                continue;

            if (n == k || k == 1)
            {
                dp[k][n] = 1;
                continue;
            }

            int newGroup = dp[k - 1][n - 1];
            int ExistingGroup = dp[k][n - 1] * k;

            dp[k][n] = newGroup + ExistingGroup;
        }
    }

    return dp[K][N];
}

void count_of_ways(int n, int k)
{
    if (n < k)
        return;

    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    // cout << count_of_ways(n, k, dp) << endl;
    cout << count_of_ways_DP(n, k, dp) << endl;

    display2D(dp);
}

// Substring and Subsquence

vector<vector<bool>> isPalindrome(string str)
{
    int n = str.length();
    vector<vector<bool>> dp(n, vector<bool>(n, 0));
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = true;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = true;
            else
                dp[i][j] = str[i] == str[j] && dp[i + 1][j - 1];
        }
    }
    return dp;
}

string longestPlaindromSubstring(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    int maxLen = 0;
    int si = 0, ei = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = 2;
            else if (str[i] == str[j] && dp[i + 1][j - 1] != 0)
                dp[i][j] = gap + 1;

            if (dp[i][j] > maxLen)
            {
                maxLen = dp[i][j];
                si = i;
                ei = j;
            }
        }
    }
    return str.substr(si, (ei - si + 1));
}

int countAllPlaindromicSubstring(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    int count = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = 2;
            else if (str[i] == str[j] && dp[i + 1][j - 1] != 0)
                dp[i][j] = gap + 1;

            count += dp[i][j] != 0 ? 1 : 0;
        }
    }
}

int longestPlaindromeSubseq_Rec(string str, int si, int ei, vector<vector<int>> &dp, vector<vector<bool>> &isPalindrome)
{
    if (isPalindrome[si][ei])
        return dp[si][ei] = ei - si + 1;
    if (dp[si][ei] != 0)
        return dp[si][ei];

    int len = 0;
    if (str[si] == str[ei])
        len = longestPlaindromeSubseq_Rec(str, si + 1, ei - 1, dp, isPalindrome) + 2;
    else
        len = max(longestPlaindromeSubseq_Rec(str, si + 1, ei, dp, isPalindrome), longestPlaindromeSubseq_Rec(str, si, ei - 1, dp, isPalindrome));

    return dp[si][ei] = len;
}

int longestPlaindromeSubseq_DP(string str, int si, int ei, vector<vector<int>> &dp, vector<vector<bool>> &isPalindrome)
{

    for (int gap = 0; gap < str.length(); gap++)
    {
        for (si = 0, ei = gap; ei < str.length(); si++, ei++)
        {

            if (isPalindrome[si][ei])
            {
                dp[si][ei] = ei - si + 1;
                continue;
            }

            int len = 0;
            if (str[si] == str[ei])
                len = dp[si + 1][ei - 1] + 2;
            else
                len = max(dp[si + 1][ei], dp[si][ei - 1]);
            dp[si][ei] = len;
        }
    }

    return dp[0][str.length() - 1];
}

// 5. Longest Palindromic Substring
// 115. Distinct Subsequences
// 516. Longest Palindromic Subsequence

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