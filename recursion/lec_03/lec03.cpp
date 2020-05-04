#include <iostream>
#include <vector>

using namespace std ;

vector<vector<int>> dirA = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
vector<string> dirS = {"L", "N", "U", "E", "R", "S", "D", "W"};

// FloodFill question in void type;
int floodFill(int sr, int sc, int er, int ec, vector<vector<int>> &board, string ans) // 0 free cell and 1 is blocked cell
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0; //mark.
    board[sr][sc] = 1;
    for (int d = 0; d < dirA.size(); d++)
    {
        int x = sr + dirA[d][0];
        int y = sc + dirA[d][1];
        if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] == 0)
        {
            count += floodFill(x, y, er, ec, board, ans + dirS[d]);
        }
    }
    board[sr][sc] = 0; //unmark
    return count;
}

// class Fooldfillpair is made to made to find longest and shortest path for the floodfill solution. 
class Floodfillpair{
    public :
        string path = "";
        int len ;

        Floodfillpair(string path_, int len_){
            path = path;
            len = len_;
        } 
};

// solution to find the longest path in the floodfill question.
Floodfillpair longestpath_in_floodfill(int sr, int sc, int er, int ec, vector<vector<int>> &board) // 0 free cell and 1 is blocked cell
{
    if (sr == er && sc == ec)
    {
        Floodfillpair base_Answer("",0);
        return base_Answer;
    }
    Floodfillpair my_Answer("",0);
    board[sr][sc] = 1;
    for (int d = 0; d < dirA.size(); d++)
    {
        for( int rad = 1 ; rad <= board.size() ; rad++){
            int x = sr + rad*dirA[d][0];
            int y = sc + rad*dirA[d][1];
            if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] == 0)
            {
                    Floodfillpair smallAns =longestpath_in_floodfill(x, y, er, ec, board);
                    if(my_Answer.len+1<smallAns.len+1){
                        my_Answer.len = smallAns.len + 1 ;
                        my_Answer.path = dirS[d] + to_string(rad) + smallAns.path;                  
                }
            }
        }
    }
    board[sr][sc] = 0; //unmark
    return my_Answer;
}

// shortest path in floodfill.
Floodfillpair shortestpath_in_floodfill(int sr, int sc, int er, int ec, vector<vector<int>> &board){
    if(sr==sc && er==ec){
        Floodfillpair base_Answer("",0);
        return base_Answer;
    }

    board[sr][sc]=1;
    Floodfillpair my_Answer("",board.size()*board[0].size());

    for(int d = 0 ; d<dirA.size() ; d++){
        int x = sr + dirA[d][0];
        int y = sc + dirA[d][1];
        if(x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] == 0){
            Floodfillpair small_Answer = shortestpath_in_floodfill(x,y,er,ec,board);
            if(small_Answer.len + 1 < my_Answer.len){
                my_Answer.len = small_Answer.len+1;
                my_Answer.path = dirS[d] + small_Answer.path;
            }
        }
    }
    board[sr][sc] = 0;
    return my_Answer;
}

// leetcode question collect maximum gold - question 1219===================================================================================================================================================
    int maximum_gold = 0;
    vector<vector<int>> gold_direction ={{1,0},{0,1},{-1,0},{0,-1}};

    void goldcounter(vector<vector<int>> &grid , int row , int col , int gold){
        gold += grid[row][col];
        maximum_gold = max(maximum_gold,gold);
        int ans = grid[row][col];
        grid[row][col] = 0 ;
        for(int i=0;i<4;i++){
            int x =row + gold_direction[i][0];
            int y=col + gold_direction[i][1];
            if(x>=0 && y>=0 && x<grid.size()&&y<grid[0].size()&& grid[x][y]!=0){
                goldcounter(grid,x,y,gold);
            }                   
        }
        grid[row][col] = ans;
    }

    int getMaximumGold(vector<vector<int>>& grid) {
        for(int i = 0 ; i < grid.size() ; i++ ){
            for(int j = 0 ; j < grid[0].size() ; j++){
                if(grid[i][j]!=0){
                    goldcounter(grid,i,j,0);
                }                  
            }
        }
        return maximum_gold;
    }

// leetcode question uniquepathIII - question 980==========================================================================================================================================================
int uniquePathsIII(int sr, int sc, int er, int ec, int freeCell, vector<vector<int>> &board, vector<vector<int>> &dir)
{
    freeCell--;
    if (sr == er && sc == ec)
    {
        if (freeCell == 0)
            return 1;
        return 0;
    }

    int count = 0;
    int temp = board[sr][sc];
    board[sr][sc] = -2;

    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];
        if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] >= 0)
            count += uniquePathsIII(x, y, er, ec, freeCell, board, dir);
    }

    board[sr][sc] = temp;
    return count;
}

int uniquePathsIII(vector<vector<int>> &board)
{
    vector<vector<int>> dir = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    int sr, sc, er, ec;
    int freeCell = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] != -1)
                freeCell++;
            if (board[i][j] == 1)
            {
                sr = i;
                sc = j;
            }

            if (board[i][j] == 2)
            {
                er = i;
                ec = j;
            }
        }
    }

    return uniquePathsIII(sr, sc, er, ec, freeCell, board, dir);
}


void pathType()
{
    vector<vector<int>> board(3, vector<int>(3, 0));

    //cout << floodFill(0, 0, 2, 2, board, "") << endl;

    Floodfillpair ans = longestpath_in_floodfill(0, 0, 2, 2, board);
    cout << ans.path << " " << ans.len << endl;

    // Floodfillpair ans_1 = shortestpath_in_floodfill(0,0,2,2,board);
    // cout<< ans_1.path << " " << ans_1.len << endl;
}

void solution(){
    pathType();
}

int main(){
    solution();
    return 0;
}