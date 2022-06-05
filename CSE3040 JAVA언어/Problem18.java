package cse3040mp2_2;

import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.Set;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.TreeMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;

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

@SuppressWarnings("serial")
class myMap2<K,V> extends LinkedHashMap<K,V>{
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
		
		Set<Map.Entry<String, Double>> set = map.entrySet();
		List<Map.Entry<String, Double>> list = new ArrayList<>(set);
		Collections.sort(list, new myComparator<Map.Entry<String, Double>>());
		
		Map<String, Double> sortedMap = new myMap2<>();
		for(Iterator<Map.Entry<String, Double>> iter = list.iterator();iter.hasNext();) {
			Map.Entry<String, Double> entry = iter.next();
			sortedMap.put(entry.getKey(), entry.getValue());
		}
		
		return sortedMap;
	}
	
	@SuppressWarnings("unchecked")
	static class myComparator<T> implements Comparator<T>{
		public int compare(Object o1, Object o2) {
			double v3=0;
			if(o1 instanceof Map.Entry && o2 instanceof Map.Entry) {
				Map.Entry<String, Double> e1 = (Map.Entry<String, Double>)o1;
				Map.Entry<String, Double> e2 = (Map.Entry<String, Double>)o2;
				double v1 = e1.getValue().doubleValue();
				double v2 = e2.getValue().doubleValue();
				v3=v1-v2;
			}
			if(v3>0) return 1;
			else if(v3<0) return -1;
			else return ((Entry<String, Double>) o1).getKey().compareTo(((Entry<String, Double>) o2).getKey());
		}
	}
	
}

public class Problem18 {
	public static void main(String[] args) {
		Map<String, Double> map = MapManager.readData("input.txt");
		if(map == null) {
			System.out.println("Input file not found.");
			return;
		}
		System.out.println(map);
	}
}
