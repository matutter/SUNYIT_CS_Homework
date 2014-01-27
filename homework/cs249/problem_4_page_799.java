// problem_4_page_799.java
// language: JAVA
// written by: Mathew C Utter
// September 2013
// 
import java.util.*;
import java.text.*;
import java.io.*;
import java.lang.Math;

class problem_4_page_799 {
	public static void main(String[] args) {
	int i;
    double mean=0;

	Random rand = new Random();
	ArrayList<Double> list = new ArrayList<>();
	  
	for(i=0; i<8; i++)
		list.add( new Double(rand.nextInt() % 30) );

    MyMath dev = new MyMath(list);
		
	System.out.println("The standard deviation of\n" + list + "\n is " + dev.get_stdDev() + "\n");	
	}
}


class  MyMath<T>
{
	private ArrayList<T> data;
	private double stdDev;	

	MyMath( ArrayList<T> data ) { this.data = data; if(check()) stdDev(); else die(); }
	public double get_stdDev() { return stdDev; }


	public boolean check() {
		System.out.printf(data.get(0).getClass().getName());
		if (data.get(0).getClass().getName() != "java.lang.Double") {
			System.out.println ("NOT A NUMBER");
			return false;	
		}
		System.out.println("[OK]");
		return true;
	}

	private void die() { System.exit(0); }

	public void stdDev() {
		int i;
		double buffer=0, average = 0;
		for( i=0; i<data.size();i++ ) {
			 average += (Double)data.get(i);			
		}
		average /= data.size();
		
		ArrayList<Double> means = new ArrayList<>();
		
		for( i=0; i<data.size();i++ ) {
			buffer = (Double)data.get(i) - average;
			buffer *= buffer;
			means.add(buffer);
		}

		for( i=0; i<means.size();i++ ) {
			 average += (Double)means.get(i);			
		}
		average/= means.size();

		stdDev = Math.sqrt(average);

		//System.out.println(buffer);
	}
}
