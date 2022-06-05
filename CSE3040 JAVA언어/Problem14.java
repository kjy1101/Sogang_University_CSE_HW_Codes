package cse3040mp1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

class ItemReader{
	public static boolean fileToBox(String string, FruitBox<Fruit> box) {
		File file = new File(string);
		try {
			Scanner input = new Scanner(file);
		//	System.out.println("Input file opened.");
			while(input.hasNext()) {
				String name = input.next();
			//	System.out.print(name+" ");
				double price = input.nextDouble();
			//	System.out.println(price);
				box.add2(new Fruit(name, price));
			}
			input.close();
		}catch(FileNotFoundException e) {
			System.out.println("Input file not found.");
		//	e.printStackTrace();
			return false;
		}
		return true;
	}
}
class Fruit{
	private String name;
	private double price;
	public Fruit(String string, double d) {
		this.name=string; this.price=d;
	//	System.out.println("name: "+name+", price: "+price);
	}
	public String toString() {
		return name+" "+price;
	}
	public double getprice() {
		return price;
	}
	public String getname() {
		return name;
	}
}

class FruitBox<T extends Fruit>{
	ArrayList<T> list = new ArrayList<T>();
	private int i=0;
	private double max=-1; private String maxname;
	private double min=Double.POSITIVE_INFINITY; private String minname;
	private double avg=0;
	public void add(T item) {
		list.add(item);
		while(i<list.size()) {
			System.out.println(list.get(i).toString());
			i++;
		}
	}
	public void add2(T item) {list.add(item);}
/*	public void printList() {
		while(i<list.size()) {
			System.out.println(list.get(i).toString());
			i++;
		}
	}*/
	public int getNumItems() {return list.size();}
	public String getMaxItem() {
		i=0;
		while(i<list.size()) {
			if(list.get(i).getprice()>max) {
				max=list.get(i).getprice();
				maxname=list.get(i).getname();
			}
			i++;
		}
		return maxname;
	}
	public double getMaxPrice() {
		i=0;
		while(i<list.size()) {
			if(list.get(i).getprice()>max) max=list.get(i).getprice();
			i++;
		}
		return max;
	}
	public String getMinItem() {
		i=0;
		while(i<list.size()) {
			if(list.get(i).getprice()<min) {
				min=list.get(i).getprice();
				minname=list.get(i).getname();
			}
			i++;
		}
		return minname;
	}
	public double getMinPrice() {
		i=0;
		while(i<list.size()) {
			if(list.get(i).getprice()<min) min=list.get(i).getprice();
			i++;
		}
		return min;
	}
	public double getAvgPrice() {
		i=0;
		while(i<list.size()) {
			avg+=list.get(i).getprice();
			i++;
		}
		avg/=list.size();
		return avg;
	}
}

public class Problem14 {
	public static void main(String[] args) {
		FruitBox<Fruit> box = new FruitBox<>();
		boolean rv = ItemReader.fileToBox("input_prob14.txt", box);
		if(rv == false) return;
		box.add(new Fruit("orange", 9.99));
		System.out.println("----------------");
		System.out.println(" Summary");
		System.out.println("----------------");
		System.out.println("number of items: " + box.getNumItems());
		System.out.println("most expensive item: " + box.getMaxItem() + " (" +
		box.getMaxPrice() + ")");
		System.out.println("cheapest item: " + box.getMinItem() + " (" +
		box.getMinPrice() + ")");
		System.out.printf("average price of items: %.2f", box.getAvgPrice());
	}
}
