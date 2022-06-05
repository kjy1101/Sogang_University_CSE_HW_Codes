package cse3040hw02;

interface IntSequence{
	public abstract boolean hasNext();
	public abstract int next();
}

class FibonacciSequence implements IntSequence{
	private int i, j=0, k=1;
	public boolean hasNext() {
		return true;
	}
	
	public int next() {
		if(i<=1) return i++;
		else {
			k=j+k;
			j=k-j;
			return k;
		}
	}
}

public class Problem06 {

	public static void main(String[] args) {
		IntSequence seq = new FibonacciSequence();
		 for(int i=0; i<20; i++) {
		 if(seq.hasNext() == false) break;
		 System.out.print(seq.next() + " ");
		 }
		 System.out.println(" ");
	}

}
