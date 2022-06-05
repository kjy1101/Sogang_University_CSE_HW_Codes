package cse3040mp1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

class Item{
	private String word;
	private int number=0;
	public Item(String w) {
		this.word=w;
	}
	public String getWord() {
		return word;
	}
	public int getNum() {
		return number++;
	}
	public int printNum() {
		return number;
	}
	public String toString() {
		return word+" "+number;
	}
}

class MyFileReader{
	public static boolean readDataFromFile(String string, ArrayList<Item> list) {
		File file = new File(string);
		try {
			Scanner input = new Scanner(file);
		//	System.out.println("Input file opened.");
			while(input.hasNext()) {
				String word = input.next();
				word=word.toLowerCase();
			//	System.out.println(word);
				int key=0; int index=0;
				for(Item i : list) {
					if(i.getWord().equals(word)) {
						key=1; break;
					}
					index++;
				}
				if(key==1) {
				//	System.out.println(word+" is already in the list["+index+"]");
					list.get(index).getNum();
				}
				else {
					list.add(new Item(word));
					list.get(list.size()-1).getNum();
				}
			}
			input.close();
		}catch(FileNotFoundException e) {
		//	System.out.println("Input file not found.");
		//	e.printStackTrace();
			return false;
		}
		return true;
	}
}

public class Problem15 {
	public static void main(String[] args) {
		ArrayList<Item> list = new ArrayList<>();
		boolean rv = MyFileReader.readDataFromFile("input_prob15.txt", list);
		if(rv == false) {
			System.out.println("Input file not found.");
			return;
		}
		for(Item it: list) System.out.println(it);
	}
}
