package cse3040hw01;

import java.util.Scanner;

public class Problem1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		System.out.print("ASCII code teller. Enter a letter: ");
		String myVar = in.nextLine();
//		System.out.println("You entered "+myVar);
//		System.out.println("Length is "+myVar.length());
		if((myVar.length()>1)||(myVar.length()==0)) {
			//1글자 이상
			System.out.println("You must input a single uppercase or lowercase alphabet.");
		}
		else{
			//1글자(알파벳이 아닌 글자도 포함)
//			System.out.println("1 letter");
			char alphabet = myVar.charAt(0);
			if((((int)alphabet>=65)&&((int)alphabet<=90))||(((int)alphabet>=97)&&((int)alphabet<=122)))
				System.out.println("The ASCII code of "+alphabet+" is " +(int)alphabet+".");
			else
				System.out.println("You must input a single uppercase or lowercase alphabet.");
		}
	}

}
