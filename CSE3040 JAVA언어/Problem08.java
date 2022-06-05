package cse3040hw02;

interface Shape{
	public abstract double area();
}

class Circle implements Shape{
	private double r;
	public Circle(double n) { r=n; }
	public double area() {
		return r*r*Math.PI;
	}
}

class Square implements Shape{
	private double r;
	public Square(double n) { r=n; }
	public double area() {
		return r*r;
	}
}

class Rectangle implements Shape{
	private double r1, r2;
	public Rectangle(double n1, double n2) { r1=n1; r2=n2; }
	public double area() {
		return r1*r2;
	}
}

public class Problem08 {
	public static double sumArea(Shape[] array) {
		double result=0;
		for(int i=0;i<array.length;i++) {
			result += array[i].area();
		}
		return result;
	}
	
	public static void main(String[] args) {
		Shape[] arr = { new Circle(5.0), new Square(4.0),
				new Rectangle(3.0, 4.0), new Square(5.0)};
		System.out.println("Total area of the shapes is: " + sumArea(arr));
	}

}
