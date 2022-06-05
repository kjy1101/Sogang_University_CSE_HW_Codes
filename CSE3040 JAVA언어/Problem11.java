package cse3040mp1;
class PalindromeChecker{
	private static String word;
	private static int p, q;
	public static void check(String str2) {
		word=str2;
		if(checker(word)==true) System.out.println(word+" is a palindrome.");
		else System.out.println(word+" is not a palindrome.");
	}
	public static void check(int n) {
		word=Integer.toString(n);
		if(checker(word)==true) System.out.println(word+" is a palindrome.");
		else System.out.println(word+" is not a palindrome.");
	}
	private static boolean checker(String str) {
		p=0;
		q=str.length()-1;
		while(p<q) {
			if(str.charAt(p)!=str.charAt(q)) return false;
			p+=1; q-=1;
		}
		return true;
	}
}

public class Problem11 {
	public static void main(String[] args) {
		PalindromeChecker.check("abcde");
		PalindromeChecker.check("abcba");
		PalindromeChecker.check(1234);
		PalindromeChecker.check(12321);
	}
}
