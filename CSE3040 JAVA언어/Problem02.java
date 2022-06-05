package cse3040hw01;

import java.util.Random;
import java.util.Scanner;

public class Problem2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random generator = new Random();
		int randomNumber=generator.nextInt(100)+1;
	//	System.out.println(randomNumber);
		int yourChoice=0;
		int turn=0, left=1, right=100;
		while(randomNumber!=yourChoice) {
			turn++;
			System.out.print("["+turn+"] Guess a number ("+left+"-"+right+"): ");
			Scanner in = new Scanner(System.in);
			yourChoice = in.nextInt();
	//		System.out.println("Your choice is "+yourChoice);
			if((yourChoice>=left)&&(yourChoice<=right)) {
				if(yourChoice > randomNumber) {
					System.out.println("Too large!");
					right=yourChoice-1;
				}
				else if(yourChoice < randomNumber) {
					System.out.println("Too small!");
					left=yourChoice+1;
				}
			}
			else {
				System.out.println("Not in range!");
				turn--;
			}
		}
		System.out.println("Correct! Number of guesses: "+turn);
	}

}
