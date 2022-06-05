package cse3040mp1;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Text{
	private int alphabet[] = new int[26];
	public boolean readTextFromFile(String string) {
		try {
			BufferedReader input = new BufferedReader(new FileReader(string));
		//	System.out.println("Input file opened.");
			while(true) {
				String line = input.readLine();
				if(line==null) break;
			//	System.out.println(line);
				for(int i=0;i<line.length();i++) {
					if(line.charAt(i)>='A'&&line.charAt(i)<='Z') {
						alphabet[line.charAt(i)-'A']++;
					}
					if(line.charAt(i)>='a'&&line.charAt(i)<='z') {
						alphabet[line.charAt(i)-'a']++;
					}
				}
			}
			input.close();
		}catch(FileNotFoundException e) {
			System.out.println("Input file not found.");
		//	e.printStackTrace();
			return false;
		}catch(IOException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	public int countChar(char c) {
	//	System.out.print("I have to return "+alphabet[c-'a']);
		return alphabet[c-'a'];
	}
	
}

public class Problem13 {
	public static void main(String[] args) {
		Text t = new Text();
		if(t.readTextFromFile("input_prob13.txt")) {
			for(char c = 'a'; c <= 'z'; c++) {
				System.out.println(c + ": " + t.countChar(c));
			}
		}
	}
}
