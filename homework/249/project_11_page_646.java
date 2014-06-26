// project_11_page_646.java
// language: JAVA
// written by: Mathew C Utter
// September 2013
// 
import java.util.*;
import java.text.*;
import java.io.*;

class project_11_page_646 {
	public static void main(String[] args) {
	
	//Date	uborn = new Date(11,8,1991); 			// how to make a new date
	//Date	udied = new Date(2,15,2089);
	//System.out.println("Born: " + uborn); 		// how to print a date
	//Person user = new Person("mat",uborn,null); 	// making a person
	//System.out.println(user); 					// print a person
	
  boolean found;
	int individual, age, group_size = 6;			//limit of Persons in the people array
	Date pborn = new Date(1,2,2000);					//making two "seed" dates
	Date pdied = new Date(2,3,2002);	

	System.out.println("Please enter today's date: ");
	Date today = getToday();							//gets user input for date
	
	String[] names = new String[]{"Mat","Tom","Jake", "Alex", "Rebecca", "Kate"};
	Person[] people = new Person[group_size];			//array of Person's
														//fill array of people
	for (int i=0;i<group_size;i++ ){
		pborn = new Date((1*i)+1,2+(i*i),2000+i);	
		pdied = new Date((2*i)+1,3+(i*i),2002+(i*i));
		people[i] = new Person(names[i], pborn, pdied);
	}


	while (true) {      										//infinite loop
	System.out.println("Enter an age to search for people near that age (under 30)");	
	age = getInt();
  found = false;

///////////////////////////////////////////////////////////////////////////////
// Finds people by age	- SEARCH -
	for (int i=0;i<group_size;i++ )
	{	
		if( people[i] != null ) { 						// wont compare things to null values, causes error
		if( people[i].get_died() != null )
			individual = people[i].get_died().get_year() - people[i].get_born().get_year();
		else
			individual = today.get_year() - people[i].get_born().get_year();	//if they're still alive
 
		if( individual < age+4 && individual > age-4 ) {
			System.out.println(people[i]);
      found = true;
    }
		}	
	}

if( !found ) { 
  System.out.println("No persons found");
} else { 
///////////////////////////////////////////////////////////////////////////////
//search by name and null the array of people there - DROP - 
	Scanner s = new Scanner(System.in);
	System.out.println("Enter a name to delete: ");
	String name = s.nextLine();
	for (int i=0;i<group_size;i++ ){
		if( people[i] != null )
			if( people[i].get_name().equals( name ))
				people[i] = null;
	}

	serialOut group	= new serialOut(people,"outfile"); 	// serialize and output it 
	serialIn grouped = new serialIn(people,"outfile"); 	// deserialize and input it
	
	System.out.println(grouped);						// print something deserialized, could just return value
}
	System.out.println("Go again? (y/n)");				// end infinite loop?
	if( getStr().equals("n") ) System.exit(0);

	}
	}

	public static Date getToday() {
		int month, day, year;
		System.out.printf("Month:\t");
		month = getInt();
		System.out.printf("\nDay:\t");
		day = getInt();
		System.out.printf("\nYear:\t");
		year = getInt();
		System.out.printf("\n");		
		
		Date today = new Date(month,day,year);
		return today;
	}


	public static String getStr() {
		Scanner s = new Scanner(System.in);
		return s.nextLine();
	}
	public static int getInt() {
		Scanner s = new Scanner(System.in);
		return s.nextInt();
	}



}
///////////////////////////////////////////////////////////////////////////////
// takes an object and a file name, serializes the object and outputs it
class serialOut {
	public serialOut (Object obj, String name){
		try {
			FileOutputStream fo = new FileOutputStream(System.getProperty( "user.dir" ) + "/" + name);

			ObjectOutputStream out = new ObjectOutputStream(fo);
			out.writeObject(obj);
			out.close();
			fo.close();
			System.out.println("\nSaved\t" + System.getProperty( "user.dir" ) + "/ " + name);
		}catch(IOException ex) {
			ex.printStackTrace();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
// takes a object and file name, opens that file and reads it into the container
// data is stored in public variable because you cannot return values from a constructor
class serialIn {
  private    Object[] container;
	public serialIn (Object obj, String name){
		System.out.println("Reading\t" + System.getProperty( "user.dir" ) + "/ " + name + "\n\n");
		try {
			FileInputStream fin = new FileInputStream(System.getProperty( "user.dir" ) + "/" + name);
			ObjectInputStream in = new ObjectInputStream(fin);

			this.container = (Object[]) in.readObject();
      in.close();
			fin.close();
		} catch(IOException ex) {
        	ex.printStackTrace();
			return;
		} catch(ClassNotFoundException nf) {
			nf.printStackTrace();
         	return;
		}
	}

	public Object[] get_container() {
		return this.container;
	}

	public String toString() {
		String buffer = "";
		for (int i=0;i<6;i++ )
			if(this.container[i]!=null)
				buffer += this.container[i];
		return buffer;
	}
}



/* 
 Class for a person with a name and dates for birth and death. 
*/
class Date implements java.io.Serializable { 
						//private String month;
	private int month; 	// simplicity first 
	private int day, year;

	public Date() {
		this.month=0;
		this.day  =0;
		this.year =0;
	}

	public Date(Date date) {
		this.month= date.get_month();
		this.day  = date.get_day();
		this.year = date.get_year();
	}

	public Date(int month, int day, int year) {
		set(month,day,year);
	}
	
	public void set(int month, int day, int year) {
		this.month=month;
		this.day  =day;
		this.year	=year;
	}


	// people can be born and die the same day!... eh...
	public boolean before(Date other){
		if ( other == null ) return true;
		if ( year	<	other.get_year() ) return true;
		if ( year	<=	other.get_year() && month	<	other.get_month() ) return true;
		if ( year <= other.get_year() && month <= other.get_month() && day < other.get_day()) return true;

		return false;
	}

	public int get_month()	{ return this.month; }
	public int get_day() 	{ return this.day; }
	public int get_year() 	{ return this.year; }
	
	public String toString() {
		return(this.month +"/"+ this.day +"/"+ this.year);
	}

}




class Person implements java.io.Serializable { 
	private String name; 
	private Date born; 
	private Date died; //null indicates still alive.
	private int  age; 

	public Person() {
	name = "";
	born = new Date(0,0,0);
	died = new Date(0,0,0);
	}

	public Person(String name, Date born, Date died) { 
		set(name, born, died);
	} 

	public void set(String name, Date born, Date died) {
  		if (born.before(died)) { 
			this.name = name; 
			this.born = new Date(born); 
			if (died == null)
				this.died = null; 
			else 
				this.died = new Date(died); 
		} else { 
			System.out.println("Inconsistent dates.Aborting."); 
			System.exit(0); 
		} 
	}

	// PERSON COPY FROM another person
	public Person(Person original) { 
		if (original == null ) { 
			System.out.println("Fatal error: Cannot make copy empty copy.\n"); 
			System.exit(0); 
		} 
		this.name = original.get_name(); 
		this.born = new Date(original.get_born()); 
		if (original.died == null) 
			this.died = null; 
		else 
			this.died = new Date(original.get_died()); 
 	} 
	// compares two People based on their to string
	public boolean equals(Person other) { 
		return (toString() == other.toString());
	}

	public boolean date_equal(Person other) { 
		return (born == other.get_born() && died == other.get_died());
	}
///////////////////////////////////////////////////////////////////////////
//SETTERS
//Precondition: newDate is a consistent date of birth. 
//Postcondition: Date of birth of the calling object is newDate. 
	public void setBirthDate(Date born) { 
		if (born.before(died)) 
		this.born = new Date(born); 
		else { 
			System.out.println("Inconsistent dates. Aborting."); 
			System.exit(0); 
		} 
	}
	public void setDeathDate(Date died) { 
		if (!died.before(born)) 
		this.died = new Date(died); 
		else { 
			System.out.println("Inconsistent dates. Aborting."); 
			System.exit(0); 
		} 
	}
	public void setName(String name) { 
		this.name = name; 
	} 
//END - SETTERS
///////////////////////////////////////////////////////////////////////////

	public String get_name(){ return name; }
	public Date get_born()	{ return born; }
	public Date get_died()	{ return died; } 

	public String toString() {
		if( died == null )
		return ("\nName: " + name + 
				"\nBorn: " + born +
				"\nDied: " + "" + "\n");
		else
		return ("Name: " + name + 
				"\nBorn: " + born +
				"\nDied: " + died + "\n");
	}
} 
