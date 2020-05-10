
class lec07{

    public static void main(String[] args){
        solve();
    }

    public static void solve() {
        wordBreak();    
    }
    public static void wordBreak(){
        String str="ilikesamsungandmangoandicecream";
        System.out.println(wordBreak(str,0,""));
    }


    public static String[] words={"mobile","samsung","sam","sung", 
        "man","mango","icecream","and", 
        "go","like","i","ice","cream","ilik","esa"};
        
    public static boolean isContains(String word){
        for(String s: words) if(s.equals(word)) return true;
                return false;
    }
        
    public static int wordBreak(String str,int idx,String ans){
        if(idx==str.length()){
            System.out.println(ans);
            return 1;
        }
        int count=0;
        for(int i=idx+1;i<=str.length();i++){
            String smallStr=str.substring(idx,i);
            if(isContains(smallStr))
            count+=wordBreak(str,i,ans+ smallStr + " ");
        }

            return count;
    }

}