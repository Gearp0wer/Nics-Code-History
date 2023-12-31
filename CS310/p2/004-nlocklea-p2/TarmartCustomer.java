/**
 *  This class represents a single Tarmart customer.
 *  Version: 1.1
 *  Last Edited: 2/23/22
 *  @author K. Raven Russell and Nicholas Locklear
 */
class TarmartCustomer {
	/**
	 * The class variable.
	 * @param numItems is the number of items in the cart.
	 */
	private int numItems;
	/**
	 * Sets up a person object with a given number of items.
	 * This is the class constructor, throws an Illegal Argument Exception if fed a number less than 1.
	 * @param numItems is the number of items in the cart.
	 */
	public TarmartCustomer(int numItems) {
		//O(1)
		//throws an IllegalArgumentException if numItems is
		//invalid (the person has less than one item)
		if(numItems < 1){
			throw new IllegalArgumentException();
		}
		else{
			this.numItems = numItems;
		}
	}
	/** 
	 * A simple getter method. Gets how many items the person still has.
	 * @return returns an integer representing the number of items in the customer's cart.
	*/
	public int getNumItems() {
		return numItems;
	}

	/**
	 * Removes one item from this person (i.e. "checks out" one item from this person.
	 * no return, no parameter.
	 */
	public void removeItem() {
		numItems -= 1;
	}
	/**
	 * Indicates whether or not this person has any more items left to "check out".
	 * @return boolean representing if the customer has an empty cart or not. 
	 */
	public boolean done() {
		if(getNumItems() > 0 ){
			return false;
		}
		else{
			return true;
		}
	}
	
	//-------------------------------------------------------------
	// Main Method For Your Testing -- Edit all you want
	//-------------------------------------------------------------
	/**
	 * The main function, some testing print statements are kept.
	 * @param args is the string array representing any arguments made on the command line. 
	 */
	public static void main(String[] args){
		TarmartCustomer mason = new TarmartCustomer(2);
		if (mason.getNumItems() == 2 && !mason.done()){
			System.out.println("Yay 1");
		}
		
		mason.removeItem();
		boolean ok = (mason.getNumItems() == 1);
		mason.removeItem();
		if ( ok && mason.done()){
			System.out.println("Yay 2");
		}
	}
	
	//-------------------------------------------------------------
	// DO NOT EDIT ANYTHING BELOW THIS LINE EXCEPT TO ADD JAVADOCS
	//-------------------------------------------------------------
	
	/**
	 * an override of the toString method, to help with printing customers. 
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return "TC("+getNumItems()+")";
	}
}