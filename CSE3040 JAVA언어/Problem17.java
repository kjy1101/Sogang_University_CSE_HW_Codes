package cse3040mp2;

import java.io.File;
import java.io.IOException;
import java.util.TreeMap;
import java.util.Map;
import java.util.Scanner;

@SuppressWarnings("serial")
class myMap<K,V> extends TreeMap<K,V>{
	private String str="";
	public String toString() {
		for(Map.Entry<K, V> e : this.entrySet()) {
			str+=e.getKey();
			str+=" ";
			str+=e.getValue().toString();
			str+="\n";
		}
		return str.trim();
	}
}

class MapManager{
	public static Map<String, Double> readData(String string) {
		Map<String, Double> map = new myMap<>();
		File file = new File(string);
		try {
			Scanner input = new Scanner(file);
			while(input.hasNext()) {
				String name = input.next();
				double price = input.nextDouble();
				map.put(name, price);
			}
			input.close();
		}catch(IOException e) {
				return null;
		}
		return map;
	}
}


public class Problem17 {
	public static void main(String[] args) {
		Map<String, Double> map = MapManager.readData("input.txt");
		if(map == null) {
			System.out.println("Input file not found.");
			return;
		}
		System.out.println(map);
	}
}
