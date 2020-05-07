//1st may lecture;
#include <iostream>

using namespace std;

void printInc(int a,int b){
    if(a==b+1){
        return ;
    }
    cout << a << " " << endl;
    printInc(a+1,b);

}

void printdec(int a,int b){
    if(a==b+1){
        return;
    }
    printdec(a+1,b);
    cout << a << " " << endl;
}

void printIncDec(int a , int b){
    if(a == b+1){
        return;
    }
        printIncDec(a+1,b);
        cout << a << " " << endl;
        printIncDec(a+1,b);
}

void basics(){
    int a,b;
    cin>>a>>b;
    //printInc(a,b);
    //printdec(a,b);
    printIncDec(a,b);
}

void solve(){
    basics();
}

int main(){

    solve();
    return 0;

}