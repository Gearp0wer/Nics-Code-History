/**
 *  This class implements a BST.
 *  
 *  @param <T> the type of the key.
 *
 *  @author W. Masri and Nicholas Locklear
 */
class BST<T extends Comparable<T>> {
	// **************//
	// DO NO CHANGE
	/**
	 *  Node class.
	 *  @param <T> the type of the key.
	 */
	class Node<T extends Comparable<T>> 
	{
		/**
		*  key that uniquely identifies the node.
		*/
		T key;
		/**
		*  references to the left and right nodes.
		*/
		Node<T> left, right;
		public Node(T item) {  key = item; left = right = null; }
		public String toString() { return "" + key; }
	}
	
	/**
	 *  The root of the BST.
	 */
	Node<T> root;
	public BST() { root = null; }
	public String toString() { return inorderToString(); }
	// DO NO CHANGE
	// **************//
	
	
	/**
	 *  This method returns a string in which the elements are listed in an inorder fashion. 
	 *  Your implementation must be recursive.
	 *  Note: you can create private helper methods
	 *  @return string in which the elements are listed in an inorder fashion
	 */
	public String inorderToString(){
		String builder = inOrder(root, "");
		//System.out.println(builder);
		return builder.trim();
	}
	/**
	 * This is the recursive implementation for inorderToString. 
	 * it builds a string recursively by traveling the nodes in order and concatenating their data to the string
	 * @param root given the root of the tree, and each subsequent node as the method traverses the tree. 
	 * @param string this is the built string
	 * @return returns a string built from traveling inorder over the nodes	
	 */
	private String inOrder(Node<T> root, String string) {
		if (root.left != null){
			string = inOrder(root.left, string);
		}
		string += "\"" + root.key.toString() + "\"" + " ";
		if (root.right != null){
			string = inOrder(root.right, string);
		}
		return string;
	}

	/**
	 *  This method inserts a node in the BST. You can implement it iteratively or recursively.
	 *  Note: you can create private helper methods
	 *  @param key to insert
	 */
	public void insert(T key) { 
		this.root = insertRec(root, key);
		//System.out.println("Root: " + root.key.toString());
	}

	   /**
		*  A recursive function to insert a new key in BST.
		* @param root starts as the root, recursively is used to store the current node
		* @param key this is the key we are trying to input
		* @return a new node
	    */
    private Node<T> insertRec(Node<T> root, T key){
        /* If the tree is empty,
           return a new node */
        if (root == null){
            root = new Node<T>(key);
            return root;
        }
		else{
			if (key.compareTo(root.key) < 0){
				root.left = insertRec(root.left, key);
			}
			else if (key.compareTo(root.key) > 0){
				root.right = insertRec(root.right, key);
			}
		}
		return root;
    }

	/**
	 *  This method finds and returns a node in the BST. You can implement it iteratively or recursively.
	 *  It should return null if not match is found.
	 *  Note: you can create private helper methods
	 *  @param key to find
	 *  @return the node associated with the key.
	 */
	public Node<T> find(T key){ //make this recursive
		//System.out.println("findRoot: " + root.key.toString());
		Node<T> thisRoot = root;
		if(key.compareTo(root.key) == 0){
			return root;
		}
		else{
			//System.out.println("Looking For: " + key.toString());
			return findRec(thisRoot, key);
		}
	}	 
	/** This is a recursive method to recursively locate nodes in a tree.
	 * 
	 * @param inputRoot this is the root we are starting from
	 * @param key this is the key whose node we are trying to find
	 * @return the node marked by the key, or null if no node is found
	 */
	private Node<T> findRec(Node<T> inputRoot, T key){//revisit this when 
		if(inputRoot == null){
			return null;
		}
		if(key.compareTo(inputRoot.key) == 0){
			return inputRoot;
		}
		if(key.compareTo(inputRoot.key) < 0){
			if(inputRoot.left == null ){
				return null;
			}
			//System.out.println("findRootL: " + inputRoot.left.key.toString());
			return findRec(inputRoot.left, key);
		}
		else{
			if(inputRoot.right == null ){
				return null;
			}
			//System.out.println("findRootR: " + inputRoot.right.key.toString());
			return findRec(inputRoot.right, key);
		}
	}

	/**
	 *  Main Method For Your Testing -- Edit all you want.
	 *  
	 *  @param args not used
	 */
	public static void main(String[] args) {
		/*
							 50
						  /	      \
						30    	  70
	                 /     \    /     \
	                20     40  60     80   
		*/
		
		
		BST<Integer> tree1 = new BST<>();
		tree1.insert(50); tree1.insert(30); tree1.insert(20); tree1.insert(40);
		tree1.insert(70); tree1.insert(60); tree1.insert(80);
		
		if (tree1.find(70) != null) {
			System.out.println("Yay1");
		}
		if (tree1.find(90) == null) {
			System.out.println("Yay2");
		}
		if (tree1.find(50) != null) {
			System.out.println("Yay3");
		}
		//System.out.println("||" + "\"20\" \"30\" \"40\" \"50\" \"60\" \"70\" \"80\"" + "||");
		if (tree1.toString().equals("\"20\" \"30\" \"40\" \"50\" \"60\" \"70\" \"80\"") == true) {
			System.out.println("Yay4");
		}
		
		
		BST<String> tree2 = new BST<>();
		tree2.insert("50"); tree2.insert("30"); tree2.insert("20"); tree2.insert("40");
		tree2.insert("70"); tree2.insert("60"); tree2.insert("80"); 
		
		if (tree2.find("70") != null) {
			System.out.println("Yay5");
		}
		if (tree2.find("90") == null) {
			System.out.println("Yay6");
		}
		if (tree2.find("50") != null) {
			System.out.println("Yay7");
		}
		if (tree2.toString().equals("\"20\" \"30\" \"40\" \"50\" \"60\" \"70\" \"80\"") == true) {
			System.out.println("Yay8");
		}
	}
	
}
