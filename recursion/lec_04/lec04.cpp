//5th may lecture 

#include <iostream>
#include <vector>

using namespace std;

int pemutation_coin_changer_coin_available_inf(vector<int> &arr, int target, string ans ){
    if(target == 0){
        cout << ans << endl ;
        return 1;
    }

        int count = 0 ;
        for(int element : arr)
                if(target-element >= 0)
                    count += pemutation_coin_changer_coin_available_inf( arr, target - element, ans + to_string(element) + " ");
        return count;
}

int permutation_coin_changer(vector<int> &arr, int target, string ans){
    if(target == 0){
        cout<< ans << endl ;
        return 1;
    }
    int count = 0 ;
    for(int i = 0 ; i<arr.size() ; i++){
        int temp = arr[i];
            if(arr[i]>0 && target - arr[i] >=0 ){
                arr[i] = -arr[i];
                count += pemutation_coin_changer_coin_available_inf( arr, target - temp, ans + to_string(temp) + " ");
                arr[i] = -arr[i];
            }
        }
    return count;
}

int combination_coin_changer_coin_available_inf(vector<int> &arr, int target , int index , string ans){
    if(target == 0){
        cout<< ans << endl ;
        return 1;
    }    

    int count = 0;
    for(int i = index ; i<arr.size() ; i++){
            count += combination_coin_changer_coin_available_inf(arr,target-arr[i],i,ans+ to_string(arr[i]) + " ");
    }
    return count;
}

int combination_coin_changer(vector<int> &arr, int target , int index , string ans){
    if(target == 0){
        cout<< ans << endl ;
        return 1;
    }
    int count = 0 ;
    for(int i = index ; i<arr.size() ; i++){
        if(target - arr[i] >=0){
            count += combination_coin_changer(arr,target-arr[i],i+1,ans+to_string(arr[i])+" ");
        }
    }
    return count;
}

void coin_changer(){
    vector<int> arr{2,3,5,7};
    int tar = 10 ;
    //cout<<pemutation_coin_changer_coin_available_inf(arr,tar,"")<<endl;   
    //cout<<combination_coin_changer_coin_available_inf(arr,tar,0,"")<<endl;
    //cout<<combination_coin_changer(arr,tar,0,"")<<endl;
    //cout<<permutation_coin_changer(arr,tar,"")<<endl;
}


//queens permutation combination ===============================================================================================================================================================================

int queensCombination(vector<bool> &rooms, int room, int qpsf, int tnq, string ans) // qpsf: queen place so far.
{
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int r = room; r < rooms.size(); r++)
        count += queensCombination(rooms, r + 1, qpsf + 1, tnq, ans + "Q" + to_string(qpsf) + "R" + to_string(r) + " ");

    return count;
}

int queensPermutation(vector<bool> &rooms, int room, int qpsf, int tnq, string ans) // qpsf: queen place so far.
{
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int r = room; r < rooms.size(); r++)
        if (!rooms[r])
        {
            rooms[r] = true;
            count += queensPermutation(rooms, 0, qpsf + 1, tnq, ans + "Q" + to_string(qpsf) + "R" + to_string(r) + " ");
            rooms[r] = false;
        }

    return count;
}

void queenProblem()
{
    vector<bool> rooms(16, false);
    int tnq = 4;
    cout << queensCombination(rooms, 0, 0, tnq, "") << endl;
    // cout << queensPermutation(rooms, 0, 0, tnq, "") << endl;
}


void solution(){
    coin_changer();
    queenProblem();
}

int main(){
    solution();
    return 0;
}
