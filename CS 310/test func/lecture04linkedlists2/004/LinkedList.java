public class LinkedList<T> {
	private Node<T> head;
	private Node<T> tail;
	
	void append(T elem) {
		Node<T> newNode = new Node<T>();
		newNode.data = elem;
		
		//if list is empty
		if(head == null) {
			head = tail = newNode;
		}
		//if list is not empty
		else {
			tail.next = newNode;
			tail = tail.next; //tail = newNode; //<-- also works
		}
	}
	
	T get(int index) {
		//we really need to do error checking on the index before
		//any of the code below is run...
		//<0 is definitely out
		//>= size is also out, so we can track the size in methods like
		//append(), insert(), remove(), etc.
		
		Node<T> curr = head;
		int count = 0;
		
		//if we do error checking on the index, we don't
		//need to check if curr is null
		while(curr != null && count < index) {
			count++;
			curr = curr.next;
		}
		
		//if we don't do error checking, we could get
		//a NullPointerException here
		return curr.data;
	}
	
	void print() {
		Node<T> curr = head;
		while(curr != null) {
			//do something with curr
			System.out.println(curr.data);
			curr = curr.next;
		}
	}
	
	public static void main(String[] args) {
		LinkedList<Character> ll = new LinkedList<>();
		ll.append('A');
		ll.append('B');
		ll.append('C');
		ll.print();
		
		System.out.println(ll.get(3));
	}
	
	private static class Node<T> {
		T data;
		Node<T> next;
	}
}