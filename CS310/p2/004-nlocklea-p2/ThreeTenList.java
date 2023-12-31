import java.util.AbstractList;
import java.util.NoSuchElementException;
import java.util.Iterator;

//READ THE DOCUMENTATION for AbstractList for more information
//on how these methods should work and when exceptions should
//be thrown. This data structure does not allow adding null
//elements.

/**
 *  A simple linked list class based on AbstractList.
 *  
 *  @param <T> the type of the item the list will contain
 *  @author K. Raven Russell and YOUR_NAME_HERE
 */
class ThreeTenList<T> extends AbstractList<T> {
	/**
	 * This class is a list extending the abstract framework for a list. 
	 * It represents, in this project specifically, a variety of functions that we inhereit and use on lines of customers
	 * @param head is a pointer looking at the head of the doubly linked list.
	 */
	protected DoubleNode<T> head = null;

	/** A pointer that always points to the "last" node in the structure. 
	 *  @param tail is a pointer looking at the tail of the doubly linked list. 
	 */
	protected DoubleNode<T> tail = null;

	/** It's an int used to count entries. 
	 * @param counter is a counter used to track the number of nodes in the list. 
	 */
	protected int counter;
	
	/**
	 * A standard constructor for the class. initializes head and tail each with pointing at a node that has null data and 
	 * is overwritten when the 1st node is added. 
	 * in retrospect, I should have just kept the pointers null. 
	 */
	public ThreeTenList() {
		counter = 0;
		DoubleNode<T> newNode = new DoubleNode<T>();
		newNode.value = null;
		head = tail = newNode;
	}
	
	/**
	 * This is a getter method to return an int representing the size (number of nodes) of the structure. 
     * {@inheritDoc}
    */
	@Override
	public int size(){
		return counter;
	}

	/**
	 * This is a getter method that returns the generic value contained within the node at the desired index. 
	 * Will also throw an exception if no elemennt is present. 
    * {@inheritDoc}
    */
	@Override
	public T get(int input){
		DoubleNode<T> curr = head;
		int count;
		for(count = 0; count < input; count++) {
			//System.out.print(curr.value);
			curr = curr.next;
		}
		//System.out.println("Req:" + input + "val:" + curr.value);
		return curr.value;
	}

	/**
    * {@inheritDoc}
    */
	@Override
	public T set(int index, T data){
		DoubleNode<T> curr = head;
		T oldData;
		for(int i = 0; i < index; i ++){
			//System.out.print(curr.value);
			curr = curr.next;
		}
		oldData = curr.value;
		curr.value = data;
		return oldData;
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
    * {@inheritDoc}
    */
	@Override
	public void add(int index, T input){
		DoubleNode<T> node = new DoubleNode<T>(input) ;
		DoubleNode<T> curr = head;
		int count = 0;
		while(curr.next != null && count < index) {
			count++;
			curr = curr.next;
		}
		node.prev = curr.prev;
		node.next = curr;
		node.prev.next = node;
		node.next.prev = node;
		counter +=1;

	}

	/**
	 * this should find the node, set the previous node to point to curr.next, and the next node's previous to curr.previous
    * {@inheritDoc}
    */
	@Override
	public T remove(int index){ //rewrite remove func
		DoubleNode<T> curr = head;
		if(size() == 0 || index >= size()){
			return null;
		}
		for(int i = 0; i < index; i++) {
			curr = curr.next;
		}
		T oldNode = curr.value;
		//System.out.println(oldNode.toString());
		if (head == null)
            return null;
        // Store head node
        DoubleNode<T> temp = head;
        // If head needs to be removed
        if (index == 0) {
            head = temp.next; // Change head
            return temp.value;
        }
        // Find previous node of the node to be deleted
        for (int i = 0; temp != null && i < index - 1; i++){
            temp = temp.next;
		}
        // If position is more than number of nodes
        if (temp == null || temp.next == null){
            return null;
		}
        // Node temp->next is the node to be deleted
        // Store pointer to the next of node to be deleted
        DoubleNode<T> next = temp.next.next;
        temp.next = next; // Unlink the deleted node from list
		//System.out.println("is now:" + curr.value.toString());
		//System.out.println("next up:" + curr.next.value.toString());
		counter -=1;
		return oldNode;
	}
	//-------------------------------------------------------------
	// Main Method For Your Testing -- Edit all you want
	//-------------------------------------------------------------
	
	/**
	 *  A main method for testing.
	 *  Print statements left in for posterity. 
	 *  @param args not used
	 */
	public static void main(String[] args){
		ThreeTenList<Character> letters = new ThreeTenList<>();
		for (int i=0; i<5; i++)
			letters.add((char)(97+i*2));
			
		if (letters.size() == 5 && letters.get(0) == 'a'){
			System.out.println("Yay 1");
		}
		
		if (letters.set(1,'b') == 'c' && letters.get(1) == 'b'){
			System.out.println("Yay 2");
		}
		
		letters.add(2,'c');
		if (letters.size() == 6 && letters.get(2) == 'c' && letters.get(3)=='e'){
			System.out.println("Yay 3");
		}
		for(int i = 0; i < letters.size(); i++){
			System.out.print(letters.get(i) + " ");
		}
		if (letters.remove(3)=='e' && letters.size() == 5 && letters.get(3)=='g'){
			System.out.println("Yay 4");
		}
		System.out.println();
		for(int i = 0; i < letters.size(); i++){
			System.out.print(letters.get(i) + " ");
		}
		System.out.println();
	}

	
	//-------------------------------------------------------------
	// DO NOT EDIT ANYTHING BELOW THIS LINE EXCEPT TO ADD JAVADOCS
	//-------------------------------------------------------------
	/**
	 * This is a class representing the "node" part of the linked list nodes.
	 * @param <T> is a generic. In this case we use it to hold the nodes' data. 
	 */
	public static class DoubleNode<T> {
		//Note: it is a bad practice to have this public, but it makes it
		//easier for us to test your implementation.
		/** Node data of type generic.
		 * @param value is the generic value held by each node.
		 */
		public T value;
		/** a pointer used to link nodes going forward.
		 * @param next is a pointer to the next node in the structure. 
		 */
		public DoubleNode<T> next;

		/** a pointer used to link nodes going backward.
		 * @param prev is a pointer to the previous node in the structure. 
		 */
		public DoubleNode<T> prev;
		
		/**
		 * a constructor. 
		 */
		public DoubleNode() { }

		/**
		 * the real constructor, takes a value and sets the node's generic to this value. 
		 * @param value is a generic representing the data we want stored on the node. 
		 */
		public DoubleNode(T value) { this.value = value; }
	}
	
	/**
	 * A tostring method. Nothing fancy. Forget if this overrides or not...
	 * @return a string value concatenating the nodes' values. 
	 */
	public String toString(){
		StringBuilder sb = new StringBuilder("");
		for (T value : this){
			sb.append(value);
			sb.append(" ");
		}
		return sb.toString();
	}
	
	/**
	 * Its an iterator that returns the next node on the structure. 
	 * @return the next node on the structure(provided it isnt null)
	 */
	public Iterator<T> iterator() {
		return new Iterator<T>() {
			DoubleNode<T> current = head;
			
			public T next() {
				if(!hasNext()) throw new NoSuchElementException();
				T val = current.value;
				current = current.next;
				return val;
			}
			
			public boolean hasNext() {
				return (current != null);
			}
		};
	}
}