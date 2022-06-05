package cse3040mp1;
class SubsequenceChecker{
	private static String str1, str2;
	private static int index[];
	private static int idx1=0, idx2=0;
	public static void check(String str_1, String str_2) {
		str1=str_1; str2=str_2;
		idx1=0; idx2=0;
	//	System.out.println("str1 is "+str1+" and length is "+str1.length());
	//	System.out.println("str2 is "+str2+" and length is "+str2.length());
		index = new int[str2.length()];
		while(idx1<str1.length()&&idx2<str2.length()) {
			if(str1.charAt(idx1)==str2.charAt(idx2)) {
				index[idx2]=idx1;
				idx2++;
			}
			idx1++;
			if(idx2==str2.length()) {
				System.out.println(str2+" is a subsequence of "+str1);
				for(int i=0;i<str2.length();i++) {
					System.out.print(index[i]+" ");
				}
				System.out.println(" ");
				break;
			}
		}
		if(idx2!=str2.length()) System.out.println(str2+" is not a subsequence of "+str1);
	}
}

public class Problem12 {
	public static void main(String[] args) {
		SubsequenceChecker.check("supercalifragilisticexpialidocious", "pads");
		SubsequenceChecker.check("supercalifragilisticexpialidocious", "padsx");
	}
}