package cse3040hw02;

class Point{
	private double[] arr;
	public Point(double[] array) {
		arr = new double[array.length];
		for(int i=0;i<array.length;i++) {
			arr[i]=array[i];
		}
	}
	public void print() {
		for(int i=0;i<arr.length;i++) {
			System.out.print("array["+i+"] is "+arr[i]+" ");
		}
		System.out.println(" ");
	}
	public double[] getArray() {
		return arr;
	}
}

interface Distance{
	public static double getDist(Point p1, Point p2) { return 0;}
}

class EuclideanDistance implements Distance{
	private static double[] arr1, arr2;
	private static double sum;
	public static double getDist(Point p1, Point p2) {
		arr1=p1.getArray();
		arr2=p2.getArray();
		if(arr1.length != arr2.length) return -1;
		for(int i=0;i<arr1.length;i++) {
			sum += (arr1[i]-arr2[i])*(arr1[i]-arr2[i]);
		}
		sum = Math.sqrt(sum);
		return sum;
	}
}

class ManhattanDistance implements Distance{
	private static double[] arr1, arr2;
	private static double sum;
	public static double getDist(Point p1, Point p2) {
		arr1=p1.getArray();
		arr2=p2.getArray();
		if(arr1.length != arr2.length) return -1;
		for(int i=0;i<arr1.length;i++) {
			if(arr1[i]>=arr2[i]) {
				sum += (arr1[i]-arr2[i]);
			}
			else
				sum += (arr2[i]-arr1[i]);
		}
		return sum;
	}
}

public class Problem09 {

	public static void main(String[] args) {
		Point p1 = new Point(new double[] {1.0, 2.0, 3.0});
		Point p2 = new Point(new double[] {4.0, 5.0, 6.0});
		System.out.println("Euclidean Distance: " + EuclideanDistance.getDist(p1, p2));
		System.out.println("Manhattan Distance: " + ManhattanDistance.getDist(p1, p2));
		Point p3 = new Point(new double[] {1.0, 2.0, 3.0});
		Point p4 = new Point(new double[] {4.0, 5.0});
		System.out.println("Euclidean Distance: " + EuclideanDistance.getDist(p3, p4));
		System.out.println("Manhattan Distance: " + ManhattanDistance.getDist(p3, p4));
	}

}
