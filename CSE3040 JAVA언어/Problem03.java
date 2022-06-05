package cse3040hw01;

import java.util.Scanner;

public class Problem3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a text: ");
		String myVar = in.nextLine();
		String s;
		char c=' ';
		do {
			System.out.print("Enter a letter: ");
			s = in.nextLine();
			if((s.length()>1)||(s.length()==0)) {
				System.out.println("You must enter a single letter.");
			}
			else {
				c = s.charAt(0);
		//		System.out.println("text is [ "+myVar+" ]");
		//		System.out.println("letter is [ "+c+" ]");
			}
		}while(s.length()!=1);
		int count=0;
		for(int i=0;i<myVar.length();i++) {
			if(myVar.charAt(i)==c) count++;
		//	System.out.print(myVar.charAt(i)+" | ");
		}
		System.out.println("There are "+count+" "+c+"'s in the text.");
	}

}
