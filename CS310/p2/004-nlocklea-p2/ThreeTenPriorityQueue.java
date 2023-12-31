import java.util.NoSuchElementException;
import java.util.Date; //for testing
/**
 * priority queue where the minimum item (the line with the fewest items) has the highest priority.
 * @param <T> is the generic, in this case a queue of lines, where each line contains people with items. 
 * @author K. Raven Russell and Nicholas Locklear
 */

class ThreeTenPriorityQueue<T extends Comparable<T>> extends ThreeTenQueue<T> {


	/**
	 * update is a method that takes the item input, and updates its position in the queue.
	 * this is done by removing the matching node, and then re adding it where it is automatically sorted.
	 * @param item a generic item to be updated. 
	 */
	public void update(T item) {
		int index = locator(item);
		//System.out.println("Index: " + index + " Item: " + get(index) + " Should be: " + item);
		if(index == -1){
			throw new NoSuchElementException();
		}
		T input = remove(index);
		//System.out.println("Removed: " + input);
		if(item != null){
			add(input);
			sortList();
		}
		
		/* Steps:
		 * 1) find matching val in list, or throw nosuchelement o(n). get index [DONE]
		 * 2) remove item from queue o(n) w remove (index)
		 * 3) re add item to queue o(n)
		 * 4) item, on adding, is sorted into best fit space
		*/
		//O(n)
	}

	/**
	 * I can't be bothered anymore, I can't take it. I'm breaking the Big O HERE AND HERE ONLY to sort this linked list
	 */
	public void sortList() {
		DoubleNode<T> current = null, index = null;  
		T temp;  
		//Check whether list is empty  
		if(head == null) {  
			return;  
		}  
		else {  
			//Current will point to head  
			for(current = head; current.next != null; current = current.next) {   
				for(index = current.next; index != null; index = index.next) {  
					if(current.value.compareTo(index.value) > 0) {  
						temp = current.value;  
						current.value = index.value;  
						index.value = temp;  
					}  
				}  
			}  
		}
	}

	/**
     * {@inheritDoc}
     */
	@Override
	public boolean add(T input){
		//System.out.print("Input: "+ input);
		DoubleNode<T> node = new DoubleNode<T>(input) ;
		if(input == null){
			return false;
		}
		if(size() == 0){
			this.head = node;
			this.tail = node;
		}
		else{
			node.prev = tail;
			tail.next = node;
			tail = node;
		}
		//System.out.println(" node "+ node.value);
		counter += 1;
		return true;
	}

	/**
	 * A getter function, but has the added bonus of taking a generic input and finding that input's index. 
	 * @param input is the generic item we are looking for. 
	 * @return an int representing the index of the input. 
	 */
	private int locator(T input){
		DoubleNode<T> headData = head;
		for(int i = 0; i < counter; i ++){
			if(headData.value.compareTo(input) != 0){
				headData = headData.next;
			}
			if(headData.value.compareTo(input) == 0){
				return i;
			}
		}
		return -1;
	}

	/** Additionally modified to only remove and return the minimum value.
    * {@inheritDoc}
    */
	@Override
	public T remove(){
		DoubleNode<T> headData = head;
		T minimum = head.value;
		int index = 0;
		for(int i = 0; i < counter; i ++){
			if(headData.value.compareTo(minimum) >= 0){
				headData = headData.next;
			}
			if(headData.value.compareTo(minimum) <= 0){
				minimum = headData.value;
				index = i;
			}
		}	
		return super.remove(index);
	}

	/** Additionally modified to only remove and return the minimum value.
    * {@inheritDoc}
    */
	@Override
	public T poll(){
		if(size() == 0){return null;}
		T oldValue = null;
		if(head == null){
			return oldValue;
		}
		else{
			oldValue = remove();
		}
		//System.out.println(oldValue.toString());
		return oldValue;
	}
	
	//-------------------------------------------------------------
	// Main Method For Your Testing -- Edit all you want
	//-------------------------------------------------------------
	
	/**
	 *  A main method for testing.
	 *  @param args not used
	 */
	public static void main(String[] args){
		ThreeTenPriorityQueue<Date> values = new ThreeTenPriorityQueue<>();
		Date[] dates = new Date[5];
		for (int i=5; i>=1; i--){
			dates[i-1] = new Date(86400000*i);
			//System.out.println(dates[i-1]);
			values.add(dates[i-1]);
		}
		//System.out.println("____________");
		for(Date d : values) {
			System.out.println(d);
		}
		System.out.println();
		dates[3].setTime(0);
		values.update(dates[3]);
		for(Date d : values) {
			System.out.println(d);
		}	
		//System.out.println("____________");
		//System.out.println("Goal: " + values.peek() + " current:" + dates[0]);
		if(values.peek().equals(dates[3])) {
			System.out.println("\nYay 1");
		}
	}
	
	//-------------------------------------------------------------
	// DO NOT EDIT ANYTHING BELOW THIS LINE EXCEPT TO ADD JAVADOCS
	//-------------------------------------------------------------
}