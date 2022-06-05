package cse3040mp2;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;

class Element implements Comparable<Element>{
	private String name;
	private double price;
	public Element(String str, double d) {
		this.name=str; this.price=d;
	}
	public String getName() { return this.name; }
	public int compareTo(Element e) {
		if(this.price > e.price) {
			return 1;
		}else if(this.price < e.price) {
			return -1;
		}else {
			return this.name.compareTo(e.getName());
		}
	}
	public String toString() {
		return this.name+" "+this.price;
	}
}

class ElementReader{
	public static ArrayList<Element> readElements(String string) {
		ArrayList<Element> list = new ArrayList<Element>();
		File file = new File(string);

		try {
			Scanner input = new Scanner(file);
			while(input.hasNext()) {
				String name = input.next();
				double price = input.nextDouble();
				list.add(new Element(name, price));
			}
			input.close();
		}catch(IOException e) {
		//	System.out.println("IOException occurred.");
		//	e.printStackTrace();
			return null;
		}
		return list;
	}
}

public class Problem16 {
	public static void main(String[] args) {
		ArrayList<Element> list = ElementReader.readElements("input.txt");
		if(list == null) {
			System.out.println("Input file not found.");
			return;
		}
		Collections.sort(list);
		Iterator<Element> it = list.iterator();
		while(it.hasNext()) System.out.println(it.next());
	}
}
