#include <iostream>
#include <vector>

using namespace std ;

//sudko solver =======================================================

bool is_safe_to_place_sudoku(vector<vector<char>> &board , int x , int y ,int num){
    //row
    for(int i=0 ; i<9 ; i++) if(board[x][i] - '0' == num) return false;
    //col
    for(int i=0 ; i<9 ; i++) if(board[i][y] - 'o' == num) return false;
    //3*3 matrix
    x = (x/3)*3; // or x = x - x%3 ;(basically we have to remove offset)
    y = (y/3)*3; // or y = y - y%3 ;(basically we have to remove offset)
    for(int i=0 ; i<3 ; i++)
        for(int j=0 ; j<3 ; j++)
            if(board[x+i][y+j] - '0' == num) return false;
    //if all above condition satisfied;
    return true;
}

void solve_Sudoku_index(vector<vector<char>> &board){
    vector<int> calls;
    for(int i=0 ; i<9 ; i++){
        for(int j=0; j<9 ; j++){
            if(board[i][j] == '.' ){
                calls.push_back(i*9+j);
            }
        }
    }
    solve_sudoku(board,calls,0);
}

bool solve_sudoku(vector<vector<char>> &board, vector<int> calls , int idx){
    if(idx==calls.size()){
        return true;
    }

    int r = calls[idx] / 9;
    int c = calls[idx] % 9;
    
    for(int num = 1 ; num<=9 ; num++){
        if(is_safe_to_place_sudoku(board,r,c,num)){
            board[r][c] = (char)(num+'0');
            if(solve_sudoku(board,calls,idx+1))
                return true;
            board[r][c] = '.' ;
        }
    }
    return false;
}

//sudko by bits ============================================================
vector<int> srow;
vector<int> scol;
vector<vector<int>> smat;

void solve_Sudoku_index(vector<vector<char>> &board){
    srow.assign(9,0);
    scol.assign(9,0);
    smat.assign(3,vector<int>{3,0});
    vector<int> calls;
    for(int i=0 ; i<9 ; i++){
        for(int j=0; j<9 ; j++){
            if(board[i][j] == '.' ){
                calls.push_back(i*9+j);
            }
            else{
                int num = board[i][j] - '0';
                int mask = 1 << num;
                srow[i] ^= mask;
                scol[j] ^= mask;
                smat[i/3][j/3]^=mask;
            }
        }
    }
    solve_sudoku(board,calls,0);
}

bool solve_sudoku(vector<vector<char>> &board, vector<int> calls , int idx){
    if(idx==calls.size()){
        return true;
    }

    int r = calls[idx] / 9;
    int c = calls[idx] % 9;
    
    for(int num = 1 ; num<=9 ; num++){
        int mask = 1<<num;
        if((srow[r]&mask)==0 && (scol[c]&mask)==0 && (smat[r/3][c/3]&mask)==0){
            board[r][c] = (char)(num-'0');
            srow[r]^=mask;
            scol[c]^=mask;
            smat[r/3][c/3]^=mask;
            if(solve_sudoku(board,calls,idx+1))
                return true;
            board[r][c] = '.' ;
            srow[r]^=mask;
            scol[c]^=mask;
            smat[r/3][c/3]^=mask;
            
        }
    }
    return false;
}

void solve(){

}

int main(){
    solve();
    return 0;
}