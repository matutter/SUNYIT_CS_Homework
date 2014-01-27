// problem_10_page_756_part1.java
// language: JAVA
// written by: Mathew C Utter
// October 2013
// 
// purpose - using shapes and graphics class
import java.util.*;
import java.lang.*;
import java.math.*;

class problem_10_page_756_part1 {
  public static void main(String[] args) {
	Shape circle	= new Circle(4.1);
	Shape rectangle	= new Rectangle(8.8,9);
	Shape righty	= new RightTriangle("Righty!!!",9,3.22);
	Rectangle rec = new Rectangle("non-classic",3,5);
	there thing = new there();

	Shape[] obj = new Shape[4];

	obj[0] = circle;
	obj[1] = rectangle;
	obj[2] = righty;
	obj[3] = rec;
	//obj[5] = thing; this wont work because it doesnt impliment shape
	System.out.println(Arrays.toString(obj));

	}
}

class there {
	there(){}
	public String toString() { return "this is there"; }
}

interface Shape {
	String type		= "undefined";
	public String toString();
	public String Def();
	public String Data();
	public String ShowArea();
	public double Area();
	public String Name();
	public void setName(String name);
 }


class RightTriangle implements Shape, Shapes {

	//@Override
	private	String type = "Right Triangle", name=type;
	private	double o, h, a, width, area;
	RightTriangle(){  }
	RightTriangle(RightTriangle rt){
		this.name	= rt.Name();
		this.area	= rt.Area();
	}
	RightTriangle(double o, double a){
		this.o	= o;
		this.a	= a;		
		update();
	}
	RightTriangle(String name, double o, double a){
		this.name = name;
		this.o	= o;
		this.a	= a;		
		update();
	}

	// mutators
	public void setOpposite(double o)	{	this.o	= o;	update();	}
	public void setAdjacent(double a)	{	this.a	= a;	update();	}
	public void setName(String name)	{	this.name	= name;	}
	public void setHypotenuse(double h)	{	this.h	= h;	update();	}


	// methods
	public void update() { area(); hypotenuse(); }
	public void area() { this.area = (this.a*this.o)/2.0;  }
	public void hypotenuse() {
		//A^2+ B^2 = C^2
		this.h = Math.sqrt(square(o)+square(a));
		}
	public double square(double a) { return a*a; }

	//getters
	public double Area()	{ return area; }
	public String Name()	{ return name; }

	// strings
	public String toString() { return (name+":area{"+area+"}");	}
	public String Def() { return ("This shape is " + type); }    
	public String Data() { return (type+":Area={ " + area + " } Opp={ " + o + " } Adj={ " + a + " } Hyp={ " + h + " }"); }    
	public String ShowArea() { return toString(); } 


}



class Rectangle implements Shape, Shapes {

	//@Override
	private	String type = "Rectangle", name=type;
	private	double height, width, area;
	Rectangle(){  }
	Rectangle(double height, double width){ this.height = height; this.width = width; update(); }
	Rectangle(String name, double height, double width){ this.name = name; this.height = height; this.width = width; update(); }

	// mutators
	public void setHeight(double height){	this.height	= height;	update();	}
	public void setWidth(double width)	{	this.width	= width;	update();	}
	public void setName(String name)	{	this.name	= name;	}


	// methods
	public void update() { area(); }
	public void area() { this.area = height * width; }

	//getters
	public double Area()	{ return area; }
	public String Name()	{ return name; }

	// strings
	public String toString() { return (name+":area{"+area+"}");	}
	public String Def() { return ("This shape is " + type); }    
	public String Data() { return (type+":Area={ " + area + " } Height={ " + height + " } Width={ " + width + " }"); }    
	public String ShowArea() { return ""; } 

}

class Circle implements Shape, Shapes {
	//@Override
	private	String type = "Circle", name=type;
	private	double radius, circumference, area, pi;
	Circle(){ pi(); }
	Circle(double radius){ pi(); this.radius = radius; update(); }
	Circle(String name, double radius){ pi(); this.name = name; this.radius = radius; update(); }

	// mutators
	public void setRadius(double radius) {	this.radius	= radius;	update();	}
	public void setName(String name) {	this.name	= name;	}


	// methods
	public void update() { area(); circumference(); }
	public void area() { this.area = pi * ( this.radius * this.radius ); }
	public void circumference() { this.circumference = pi * this.radius*0x2; }

	//getters
	public double Radius()	{ return radius; }	
	public double Circumference()	{ return circumference; }
	public double Area()	{ return area; }
	public double Pi()	{ return pi; }
	public String Name(){ return name; }

	///////////////////////////////////////////
	// START - PI
	// for finding pi without java.math accurate to BEEF
	public void pi() {
	double pi=0.0, add_buff=0.0, sub_buff=0.0, buffer=0.0;
	double i=0, odds=1.0;
	int pos=0, neg=0;
	for(i=0;i<0xBEEF;) {
		if(i%2!=0) {
			sub_buff = 1.0 / odds;
			buffer = buffer - sub_buff;
			i++;
			neg++;
		} else {
			add_buff = 1.0 / odds;
			buffer = buffer + add_buff;
			i=i+3;
			pos++;
		}
	odds=odds+2.0;
	}
	this.pi = (4 * ( buffer ));
	}
	// END - PI
	///////////////////////////////////////////

	// strings
	public String toString() { return (name+":area{"+area+"}");	}
	public String Def() { return ("This shape is " + type); }    
	public String Data() { return (type+":Area={ " + area + " } Circumference={ " + circumference + " }"); }    
	public String ShowArea() { return ""; } 
}
