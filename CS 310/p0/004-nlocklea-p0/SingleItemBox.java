
/*
 * Author: Nicholas Locklear
 * G01090642
 * CS 310-004
 */

/**
 * A class to hold a generic object of any type.
 * @param <X> is the generic item holding an object.
 */
public class SingleItemBox<X> {
	/**
	 * The generic item of type x.
	 * @param item is what's being added.
 	 */
	private X item;
	/**
	 * The generic item of type x.
	 * @param input is the item being held.
 	 */
	public SingleItemBox(X input){
		this.item = input;
	}
	/**
	 * The generic item of type x.
	 * @return is the item being held by the class.
 	 */
	public X getItem(){
		return item;
	}
	/**
	 * The main method. 
	 * @param args is the user input.
	 */
	public static void main(String args[]){
		/**
		 * A testing class.
	 	 */
		class Apple { }
		//make an apple
		Apple a1 = new Apple();
		//put the apple in a box
		SingleItemBox<Apple> appleBox = new SingleItemBox<>(a1);
		//check that the apple was put in the box
		if(appleBox.getItem().equals(a1)) {
			System.out.println("yay 1");
		}
		/**
		 * A testing class.
	 	 */
		class Banana { }
		//make a banana
		Banana b1 = new Banana();
		//put the banana in a box
		SingleItemBox<Banana> bananaBox = new SingleItemBox<>(b1);
		//check that the banana was put in the box
		if(bananaBox.getItem().equals(b1)) {
			System.out.println("yay 2");
		}
		/**
		 * A testing class.
	 	 */
		class Cat { }
		//make a cat
		Cat c1 = new Cat();
		//put the banana in a box
		SingleItemBox<Cat> catPlayBox = new SingleItemBox<>(c1);
		//check that the banana was put in the box
		if(catPlayBox.getItem().equals(c1)) {
			System.out.println("yay 3");
		}
	}
}