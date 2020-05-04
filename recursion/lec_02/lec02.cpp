//recursion in arrays 
//second lec

#include <iostream>
#include <vector>

using namespace std;

// basic recursion in array - maximum,minmum,find====================================================================================================================

    //vector is an dynamic form of array which can grow in size;
    //use of a vector is easier as compared to an array becuase we dont have the need to declare any poiter;
    //and therefore vector is same as an array which is dynamic in nature and doest use any pointer; 

int maximum_of_array(vector<int>& arr, int index){

    if( index == arr.size() -1 )
        return arr[index];
    return max(arr[index] , maximum_of_array(arr,index+1) );

} 

int minimum_of_array(vector<int>& arr, int index){

    if( index == arr.size() -1 )
        return arr[index];
    return min(arr[index], minimum_of_array(arr,index + 1) );
    
}

bool find_in_array(vector<int>& arr, int index, int data){

    if( index == arr.size() )
        return false;
    if( arr[index] == data )
        return true;
    return find_in_array(arr,index + 1,data);

}

void recursion_with_array(){
    // Array input code;
    // int n;
    // cin >> n;
    // vector<int> arr(n,0);
    // for(int i = 0 ; i < n ; i++){
    //     cin >> arr[i];
    // }

    // Another way of arraay declaration;
    vector<int> arr{1,2,3,4,5,6,7,8,9,10};
    cout<<maximum_of_array(arr,0)<<endl;
    cout<< minimum_of_array(arr,0)<<endl;
    cout<<find_in_array(arr,0,10)<<endl;

}

// recursion in array - nokiakeypad==========================================================================================

// keypad question using return type;
vector<string> keypad(vector<string> words , string str){

    if(str.length() == 0){
        vector<string> base_ans ;
        base_ans.push_back("");
        return base_ans;
    }

    char ch = str[0];
    string nstr = str.substr(1);
    string word = words[ch - '0'];
    vector<string> small_Ans = keypad(words , nstr);
    vector<string> my_ans;

    for(string s : small_Ans){
        for(int i = 0 ; i < word.length() ; i++){
            my_ans.push_back(word[i] + s);
        }
    }
    return my_ans;

}

// keypad question using void type;
int keyPad(string question , string ans , vector<string> words){

    if(question.length() == 0 ){
        cout<<ans<<endl;
        return 1;
    }

    char ch = question[0];
    string roq = question.substr(1);
    string word = words[ch - '0'];

    int count = 0;
    for(int i = 0 ; i<word.length() ; i++){
        count+=keyPad(roq, ans + word[i], words);
    }
    return count;

}

// keypad question for number 10 and 11;
int key_Pad(int index, string question , string ans , vector<string> words){
    if(index == question.length() ){
        cout<<ans<<endl;
        return 1;
    }

    char ch = question[index];
    string word = words[ch - '0'];

    int count = 0;
    for(int i = 0 ; i<word.length() ; i++)
        count+= key_Pad(index+1,question,ans+word[i],words);
    
    if(index+1<question.length()){
        int num = (ch - '0')*10 + (question[index + 1] - '0');
        if(num == 10 || num == 11){
            word = words[num];
            for(int i = 0 ; i<word.length() ; i++){
                count+=key_Pad(index+2,question,ans+word[i],words);
            }
        }
    }
    return count;

}

void recursion_for_return_type(){

// vector input;    
    vector<string> words = {
    ":;/",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wx",
    "yz",
    "&*%",
    "#@$",
};

// for return type of string
vector<string> ans = keypad(words,"489");
for(string s : ans)
    cout<<s<<" ";

// for viod return type
cout<<keyPad("489","",words);

// for void type and num 10 or 11
cout<<key_Pad(0,"489","",words);

}

// recursion for question of path type =================================================================================================================================

//mazepath question with horizontal , vertical and diagonal movement;
vector<string> mazepath_H_V_D(int sr, int sc, int er, int ec){

if(sr==er && sc == ec){
    vector<string> base_ans;
    base_ans.push_back("");
    return base_ans;
}

vector<string> my_ans;

if( sr + 1 <= er ){
    vector<string> vertical = mazepath_H_V_D(sr+1,sc,er,ec);
    for( string s : vertical ){
        my_ans.push_back("V"+s);
    }
}

if( sc + 1 <= ec ){
    vector<string> horizontal = mazepath_H_V_D(sr,sc+1,er,ec);
    for( string s : horizontal ){
        my_ans.push_back("H"+s);
    }
}

if( sr + 1 <= er && sc + 1 <= ec ){
    vector<string> diagonal = mazepath_H_V_D(sr+1,sc+1,er,ec);
    for( string s : diagonal ){
        my_ans.push_back("d"+s);
    }
}

}

//mazepath with variable jump in return type;
vector<string> mazepath_H_V_D_multiple_steps(int sr, int sc, int er, int ec){
    if(sr==er && sc==ec){
        vector<string> base_ans;
        base_ans.push_back("");
        return base_ans;
    }

    vector<string> my_ans;

    for(int i = 1 ; sr + i <= er ; i++){
        vector<string> vertical = mazepath_H_V_D(sr+i,sc,er,ec);
        for( string s : vertical ){
            my_ans.push_back("V"+ to_string(i) +s);
        }
    }

    for(int i = 1 ; sc + i <= ec ; i++){
        vector<string> horizontal = mazepath_H_V_D(sr,sc+i,er,ec);
        for( string s : horizontal ){
            my_ans.push_back("H"+ to_string(i) +s);
        }
    }

    for(int i = 1 ; sr + i <= er && sc + i <= ec ; i++){
        vector<string> diagonal = mazepath_H_V_D(sr+i,sc+i,er,ec);
        for( string s : diagonal ){
            my_ans.push_back("d"+ to_string(i) +s);
        }
    }

}

//mazepath using void type;
int mazepath_HVD(int sr, int sc, int er, int ec, string ans){
    if(sr==er && sc==ec){
        cout<<ans<<endl;
        return 1;
    }
    int count = 0;
    if(sr+1<=er){
        count+= mazepath_HVD(sr+1,sc,er,ec,ans+"V");
    }
    if(sc+1<=ec){
        count+= mazepath_HVD(sr,sc+1,er,ec,ans+"H");
    }
    if(sr+1<=er && sc+1<=ec){
        count+= mazepath_HVD(sr+1,sc+1,er,ec,ans+"D");
    }
    return count;
}

// mazepath using voidtype with variable jumps;
int mazepath_HVD_multiple_steps(int sr, int sc, int er, int ec, string ans){
    if(sr==er && sc==ec){
        cout<<ans<<endl;
        return 1;
    }
    int count = 0;
    for(int i = 1 ; sr+i<=er ; i++){
        count+= mazepath_HVD_multiple_steps(sr+i,sc,er,ec,ans+"V"+to_string(i));
    }
    for(int i = 1 ; sc+i<=ec ; i++){
        count+= mazepath_HVD_multiple_steps(sr,sc+i,er,ec,ans+"H"+to_string(i));
    }
    for(int i = 1 ; sr+i<=er && sc+i<=ec ; i++){
        count+= mazepath_HVD_multiple_steps(sr+i,sc+i,er,ec,ans+"D"+to_string(i));
    }
    return count;
}


void recursion_for_path_return_type(){
// mazepath using return type;
// vector<string> ans = mazepath_H_V_D(0,0,3,3);
// for( string s : ans ){
//     cout<<s;
// }

// mazepath using return type with multiple jump;
// vector<string> ans_1 = mazepath_H_V_D_multiple_steps(0,0,3,3);
// for( string s : ans_1 ){
//     cout<<s;
// }

// mazepath using void type;
cout<<mazepath_HVD(0,0,3,3,"")<<endl;

//mazepath using voidtype with variable jump;
cout<<mazepath_HVD_multiple_steps(0,0,3,3,"")<<endl;

}

//recursion for floodfill problem ==================================================================================================================================

vector<vector<int>> array = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
vector<string> direction = {"L", "N", "U", "E", "R", "S", "D", "W"};

// mazepath using flood fill with 8 direction allowed;
int flood_fill(int sr, int sc , int er, int ec , vector<vector<int>> &board , string ans){
    if(sr==er && sc==ec){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    board[sr][sc]=1; // mark
    for(int i = 0 ; i<array.size() ; i++){
        for( int j = 1 ; j <= board.size() ; j++){
            int x = sr + j*array[i][0];
            int y = sc + j*array[i][1];
            if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] == 0){
                count += flood_fill(x, y, er, ec, board, ans + direction[i]);
            }
        }
    }
    board[sr][sc]=0; // unmark
    return count;
}

// rat in mazepath using floodfill
vector<vector<int>> arr = {{0,0,0,0,0,0},{0,1,0,1,0,0},{0,0,0,0,0,0},{0,0,1,0,1,0},{1,0,0,0,0,0},{0,0,0,0,0,0}};
// int rat_in_maze_path(){

// }


void recusrsion_for_floodfill(){
    //mazepath using floodfill;    
    vector<vector<int>> board(3,vector<int>(3,0));
    cout<< flood_fill(0,0,2,2,board,"")<<endl;

    //rat in a maze;

    //rat in a maze using return type

}

void solve(){
    //recursion_with_array();
    //recursion_for_return_type();
    //recursion_for_path_return_type();
    recusrsion_for_floodfill();
}

int main(){
    solve();
    return 0;
}

