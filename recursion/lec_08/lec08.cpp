#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// crypto solver========================================================================================================================================================

string str1="send";
string str2="more";
string str3="money";
int isNumberUsed=0;
vector<int> assingedNumber(26,0);

int strtoNumber(string str){
    int res=0;
    for(int i=0;i<str.length();i++){
        int temp = str[i]-'a'; 
        res=res*10+assingedNumber[temp];
    }
    return res;
}

int cryptosolver(string &str, int idx){
    if(idx==str.length()){
        int num1 = strtoNumber(str1);
        int num2 = strtoNumber(str2);
        int num3 = strtoNumber(str3);

        if((assingedNumber[str1[0]-'a']!=0) && (assingedNumber[str2[0]-'a']!=0) && (assingedNumber[str3[0]-'a']!=0) && num1+num2==num3){
            cout<<num1<<endl
                <<"+"<<num2<<endl
                <<"--------"<<endl
                <<num3<<endl;
        }
        return 0;
    }

    int count=0;
    for(int num=0; num<=9 ;num++){
        int mask =  1<<num;
        if((isNumberUsed & mask)==0){
            isNumberUsed^=mask;
            assingedNumber[str[idx]-'a']=num;
            count+=cryptosolver(str,idx+1);
            assingedNumber[str[idx]-'a']=0;
            isNumberUsed^=mask;
        }
    }
    return count;
}

void crypto(){
        string str = str1+str2+str3;
        vector<int> freq(26,0);
        for(int i = 0 ; i < str.length() ; i++)
            freq[str[i]-'a']++;
        
        str="";
        for(int i = 0 ; i < 26 ; i++)
            if(freq[i]>0)
                str+=(char)(i+'a');
        
        //cout<<str<<endl;
        cout<<cryptosolver(str,0)<<endl;

}

// leetcode 40 ======================================================================================================================================================
vector<vector<int>> combinationSum2(vector<int>& arr, int target) {
        sort(arr.begin(),arr.end());//in java Arrays.sort(arr);
        vector<vector<int>> res;
        vector<int> ans;
        combination(arr,0,target,res,ans);
        return res;
    }
    
void combination(vector<int> &arr,int idx,int tar,vector<vector<int>>& res,vector<int>& ans){
    if(tar==0){
        vector<int> base;
        for(int ele : ans) base.push_back(ele);
            res.push_back(base);
        return;
    }
    int prev = -1;
    for(int i=idx;i<arr.size();i++){
        if(prev==arr[i]){
            continue;
        }
        prev=arr[i];
        if(tar-arr[i]>=0){
            ans.push_back(arr[i]);
            combination(arr,i+1,tar-arr[i],res,ans);
            ans.pop_back();
        }
    }
}


void solution(){
    crypto();
}

int main(){
    solution();
    return 0;
}