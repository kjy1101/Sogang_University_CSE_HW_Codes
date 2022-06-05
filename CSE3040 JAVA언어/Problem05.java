package cse3040hw01;

import java.util.Scanner;

public class Problem5 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Enter exam scores of each student.");
		int firstMax=-1, secondMax=-1, idx1=0, idx2=0;
		int[] scoreArray = new int[5];
		for(int i=0;i<5;i++) {
			System.out.print("Score of student "+(i+1)+": ");
			Scanner in = new Scanner(System.in);
			scoreArray[i] = in.nextInt();
			if(scoreArray[i]>firstMax) {
				firstMax=scoreArray[i];
				idx1=i;
			}
		}
		for(int i=0;i<5;i++) {
			if(i!=idx1) {
				if(scoreArray[i]>secondMax) {
					secondMax=scoreArray[i];
					idx2=i;
				}
			}
		}
		System.out.println("The 1st place is student "+(idx1+1)+" with "+firstMax+" points.");
		System.out.println("The 2nd place is student "+(idx2+1)+" with "+secondMax+" points.");
	}

}
