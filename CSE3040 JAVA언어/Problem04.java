package cse3040hw01;

import java.util.Scanner;

public class Problem4 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a text: ");
		String myVar = in.nextLine();
		String s;
		do {
			System.out.print("Enter a string: ");
			s = in.nextLine();
			if(s.length()==0) {
				System.out.println("You must enter a string.");
			}
			else {
		//		System.out.println("length: "+s.length());
		//		System.out.println("Right input");
			}
		}while(s.length()==0);
		int count=0;
		int sLength=0;
		for(int i=0;i<myVar.length();i++) {
			for(int j=0;j<s.length();j++) {
				if(i+j<myVar.length()) {
					if(myVar.charAt(i+j)==s.charAt(j)) {
						sLength++;
					}
				}
			}
			if(sLength==s.length()) {
				count++;
			}
			sLength=0;
		}
		System.out.println("There are "+count+" instances of \""+s+"\".");
	}

}
