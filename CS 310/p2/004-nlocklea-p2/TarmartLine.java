import java.util.Queue;

/**
 *  A data structure (based on a queue) to represent a Tarmart
 *  store line. Tarmart lines can only contain people and can
 *  be compared  to eachother based on the number of items left 
 *  to process in the line. The lines also have id numbers.
 *  
 *  @author K. Raven Russell and Nicholas Locklear
 */
class TarmartLine extends ThreeTenQueue<TarmartCustomer> implements Comparable<TarmartLine> {
	/**
	 * The class variable.
	 * @param id is the identifying number representing the line.
	 */
	private int id;
	/**
	 * Creates a Tarmart line with a given ID.
	 * @param id is the id being fed to the constructor.
	 */
	public TarmartLine(int id) {
		this.id = id;
	}

	/**
	 * Standard Getter method. Returns the ID of the line.
	 * @return an integer representing the line's ID.
	 */
	public int getId() {
		return id;
	}
	
	/**
	 * Sums up all items for all customers in the line.
	 * @return an integer representing the total number of items in each customer's cart.
	 */
	public int itemsInLine() {
		DoubleNode<TarmartCustomer> headNode = this.head;
		TarmartCustomer headVal;
		int runningTotal = 0;
		for(int i = 0; i < size(); i++){
			headVal = headNode.value;
			runningTotal += headVal.getNumItems();
			//System.out.println("Line: " + this.getId() + " Node: " + i + " value: " + headVal.getNumItems());
			headNode = head.next;
		}
		return runningTotal;
	}
	
	/**
	 * an override of the comparator to specifically compare two tarmart lines.
	 * compares them by total amount of items, and then by ID.
	 * {@inheritDoc}
	 */
	@Override
	public int compareTo(TarmartLine otherLine) {
		//System.out.println("Line 1: " + getId() + " Line 2: " + otherLine.getId());
		int itemQuantity1 = itemsInLine();
		int itemQuantity2 = otherLine.itemsInLine();
		int check;
		if(itemQuantity1 == itemQuantity2){
			if(getId() == otherLine.getId()){
				check = 0;
			}
			else{
				check = getId() > otherLine.getId() ? 1 : -1;
			}
		}
		else{
			check = itemQuantity1 > itemQuantity2 ? 1 : -1;
		}
		return check;

		/*
		HINTS:
		
		Compare functions work as follows:
		Given two things (a and b) and a function call: a.compareTo(b),
		the function will return an integer less than 0 if a is less than b
		the function will return an integer greater than 0 if a is greater than b
		the function will return 0 if a and b are equal
		
		For example:
		If this line contains 5 items and otherLine contains
		100 items, then this function will return an integer
		less than 0.
		
		If this line contains 100 items and otherLine contains
		0 items, then this function will return an integer
		greater than 0.
		
		If this line contains 5 items and otherLine contains
		5 items, the ids will be compared. If this line has an
		id of 10 and otherLine has an id of 2, then this function
		will return an integer greater than 0.
		*/
		
	}
	
	/**
	 * Processes (removes) one item from the first customer in line. 
	 * If the customer has no more items they are removed from the line.
	 */
	public void processItem() {
		TarmartCustomer headData = head.value;
		//System.out.println(headData.toString());
		//System.out.println("data: " + headData.getNumItems());
		if(headData == null || headData.done() == true){
			remove(0);
		}
		else{
			headData.removeItem();
		}
		//System.out.println("newdata: " + headData.getNumItems());

	}

	/**
	 * Converts the line to a string.
	 * {@inhereit}
	 */
	@Override
	public String toString() {
		DoubleNode<TarmartCustomer> headNode = this.head;
		TarmartCustomer headVal;
		int runningTotal = 0;
		String output = getId() + ": ";
		if(size() == 0){
			output += "= 0 shopper(s) with 0 item(s)";
		}
		else{
			for(int i = 0; i < size(); i ++){
				headVal = headNode.value;
				output += "TC(" + headVal.getNumItems() + ") ";
				runningTotal += headVal.getNumItems();
				headNode = head.next;
			}
			output += "= " + size() + " shopper(s) with " + runningTotal + " item(s)";
		}
		return output;
	}
	
	//-------------------------------------------------------------
	// Main Method For Your Testing -- Edit all you want
	//-------------------------------------------------------------
	/**
	 *  A main method for testing.
	 *  Print statements left in for posterity. 
	 *  @param args not used
	 */
	public static void main(String[] args) {
		TarmartLine line = new TarmartLine(0);
		TarmartCustomer mason = new TarmartCustomer(10);
		TarmartCustomer george = new TarmartCustomer(20);
		
		line.offer(mason);
		line.offer(george);
		
		if (line.getId()==0 && line.itemsInLine() == 30){
			System.out.println("Yay 1");
		}
		
		line.processItem();		
		if (line.itemsInLine() == 29 && line.peek().getNumItems()==9){
			System.out.println("Yay 2");
		}

		TarmartLine line2 = new TarmartLine(1);
		TarmartCustomer washington = new TarmartCustomer(40);
		line2.offer(washington);
		//System.out.println("Line 1: " + line.getId() + " Line 2: " + line2.getId());
		if (line.compareTo(line2)<0){
			System.out.println("Yay 3");
		}
		System.out.println(line.get(0).toString() + " next up " + line.get(1).toString());
		for(int i = 0; i < 9; i++){
			line.get(0).removeItem();
		}
		System.out.println(line.get(0).toString());
		line.processItem();
		System.out.println(line.get(0).toString());
	}
}