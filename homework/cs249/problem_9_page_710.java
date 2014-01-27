// problem_9_page_710.java
// language: JAVA
// written by: Mathew C Utter
// September 2013
// 
import java.util.*;
import java.text.*;
import java.io.*;

class problem_9_page_710 {
	public static void main(String[] args) {

	int size = 10;

	Random generator = new Random();
	int[] ary = new int[size];

	for( int i=0; i<10; i++ )
		ary[i] = generator.nextInt(20);

	System.out.println("\nunsort:" + Arrays.toString(ary));

	sort(ary,0,size-1);

	System.out.println("  sort:" + Arrays.toString(ary));

	insert(ary,generator.nextInt(20));
	System.out.println("\n");
// BELOW FROM TEXT *some changes 
  }
	public static void insert(int [] oldary, int a) {
		int[] ary = new int[oldary.length+1];
		int i, j, hi;


		for( i=0; i<oldary.length; i++ ) {
			ary[i] = oldary[i];
		}

		for( i=0; i!=ary.length-1; i++){
			//System.out.println(ary[i]);
			if(a<ary[i])
			break;			
			}
			if( oldary[oldary.length-1]<=a )
				System.out.println("\n" + a + " will insert after " + oldary[oldary.length-1] );
			else
				System.out.println("\n" + a + " will insert before " + ary[i] );

		j=i;
		for( i=ary.length-1; i>j; i--)
			ary[i]=ary[i-1];
		ary[j]=a;

		System.out.println("insert:" + Arrays.toString(ary));

	}


	public static void sort(int [] a, int begin, int end) {
		if ((end - begin) >= 1){
			int splitPoint = split(a, begin, end);
			sort(a, begin, splitPoint);
			sort(a, splitPoint + 1, end);
			join(a, begin, splitPoint, end);
		}
	}
	
	private static int split( int [] a, int begin, int end){ 
		return ((begin + end)/2); 
	}

	private static void join( int [] a, int begin, int splitPoint, int end) {
		int[] temp;
		int intervalSize = (end - begin + 1);
		temp = new int [intervalSize];
		int nextLeft = begin; 				//index for first chunk 
		int nextRight = splitPoint + 1; 	//index for second chunk 
		int i = 0; 							//index for temp

		//Merge till one side is exhausted: 
		while ((nextLeft <= splitPoint) && (nextRight <= end)) {
			if (a[nextLeft] < a[nextRight]) {
				temp[i] = a[nextLeft];
				nextLeft++;
				i++;

			} else {
				temp[i] = a[nextRight];
				nextRight++; 
				i++;
			}
		}

		while (nextLeft <= splitPoint) {	//Copy rest of left chunk, if any.
			temp[i] = a[nextLeft];
				nextLeft++;
				i++;
		}
		while (nextRight <= end) {			//Copy rest of right chunk, if any. 
			temp[i] = a[nextRight];
			nextRight++;
			i++;
		}
		for (i = 0; i < intervalSize; i++)
			a[begin + i] = temp[i];
	}

















}// end of main


