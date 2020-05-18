#include <iostream>
#include <vector>

using namespace std;

int equiset(vector<int> arr,int idx,int set1,int set2,string set1s,string set2s){
    if(idx==arr.size()){
        if(set1==set2){
            cout<<set1s + " = " + set2s<<endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    count+= equiset(arr,idx+1,set1+arr[idx],set2,set1s+" "+to_string(arr[idx]),set2s);
    count+= equiset(arr,idx+1,set1,set2+arr[idx],set1s,set2s+" "+to_string(arr[idx]));
    return count;
}

int equiset_02(vector<int> arr,int idx,int set1,int set2,string set1s,string set2s){
    if(idx==arr.size()){
        if(set1==set2 && set1 !=0){
            cout<<set1s + " = " + set2s<<endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    count+= equiset(arr,idx+1,set1+arr[idx],set2,set1s+" "+to_string(arr[idx]),set2s);
    count+= equiset(arr,idx+1,set1,set2+arr[idx],set1s,set2s+" "+to_string(arr[idx]));
    count+= equiset(arr,idx,set1,set2,set1s,set2s);

    return count;
}

void equi(){
    vector<int> arr{10,20,30,40,50,60,70,80,90};
    //cout<<equiset(arr,0,10,0,"10","");
    cout<<equiset_02(arr,0,10,0,"10","");
}

void solve(){
    equi();
}

int main(){
    solve();
    return 0;
}