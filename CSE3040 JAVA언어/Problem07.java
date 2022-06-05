package cse3040hw02;

import java.util.Scanner;

interface IntSequenceStr{
	public abstract boolean hasNext();
	public abstract int next();
}

class BinarySequenceStr implements IntSequenceStr{
	private int number, r, result, i;

	public BinarySequenceStr(int n) { number=n; }
	public boolean hasNext() {
		if(i==0) return true;
		else return false;
	}
	public int next() {
		while(number>0) {
			r = number % 2;
			number /= 2;
			result += r*Math.pow(10, i);
			i++;
		}
		i++;
		return result;
	}
}

public class Problem07 {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		 System.out.print("Enter a positive integer: ");
		 String str = in.nextLine();
		 int num = Integer.parseInt(str);
		 in.close();
		 System.out.println("Integer: " + num);
		 IntSequenceStr seq = new BinarySequenceStr(num);
		 System.out.print("Binary number: ");
		 while(seq.hasNext()) System.out.print(seq.next());
		 System.out.println(" ");
	}

}
