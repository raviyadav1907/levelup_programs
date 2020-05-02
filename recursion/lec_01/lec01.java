import java.util.Scanner;

class lec01{

    public static Scanner scn = new Scanner(System.in);
    public static void main(String[] args) {
        solve();
    }

    public static void solve(){
        basics();
    }

    public static void basics(){

        // int n = scn.nextInt();
        // System.out.println(facto(n));

        int a = scn.nextInt();
        int b = scn.nextInt();
        //System.out.print(power(a, b));
        System.out.println(powerbtr(a, b));
    }

    public static int facto(int n){
        if(n==0){
            return 1;
        }
        int nm1 = facto(n-1);
        int facto = n*nm1;
        return facto;
    }

    public static int power(int a ,int b){
        if(b==0){
            return 1;
        }
        return power(a, b-1)*a;
    }

    public static int powerbtr(int a,int b) {
        if(b==0){
            return 1;
        }
        int halfpower = powerbtr(a, b/2);
        halfpower*= halfpower;
        return halfpower;
    }

}