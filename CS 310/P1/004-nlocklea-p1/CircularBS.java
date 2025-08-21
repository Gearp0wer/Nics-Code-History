/*
 * Author: Nicholas Locklear
 * G01090642
 * CS 310-004
 */

/**
 * CircularBS is a circular array class that holds generic items.
 * @param <T> is the generic item holding an object.
 */
public class CircularBS<T> implements CircularBSInterface<T> {
        
    /** The int variable representing capacity.
     * @param capacity is the size of the array.
     */

    private int capacity;
    /** An int representing the starting index of the entries.
     * @param startIndex The oldest entry in the array.
     */

    private int startIndex;
    /** An int representing the ending index of the entries.
     * @param endIndex The youngest entry in the array.
     */
    private int endIndex;
    /** The array holding the items.
     * @param CircularBS is the array variable.
     */
    protected T[] CircularBS;
    /** Total current entries in the array.
     * @param entities is an int representing the number of entries in the array.
     */
    private int entries;
    /**
     * The base constructor of the class. 
     */
    @SuppressWarnings("unchecked")
    CircularBS(){
        capacity = 50;
        startIndex = 0;
        endIndex = 49;
        CircularBS = (T[])new Object[capacity];
        entries = 0;
    }
    /**
     * The second constructor, used for initializing an array if an input is given.
     * @param capacity The value given to set capacity of the array.
     */
    @SuppressWarnings("unchecked")
    CircularBS(int capacity) {
        
        this.capacity = capacity;
        this.endIndex = capacity -1;
        CircularBS = (T[])new Object[capacity];
    }
    
    /**
     * The insertion method, checks if the array is full.
     * If true, it inserts the parameter item after doubling the size of the array.
     * @param newblock is the generic item being inserted into the array. 
     */
    public void insert(T newblock){
        if(isFull() == true){
            doubleCapacity();
        }
        endIndex += 1;
        CircularBS[endIndex % capacity] = newblock;
        entries += 1; 
    }
    
    /**
     * No parameters, the method used to "archive" (remove) the oldest entry from the array.
     * @return Oldest entry in the array. 
     */
    public T archive(){
        if(isEmpty() == true){
            throw new NoBlockException("No Block to process");
        }
        T output = CircularBS[startIndex % capacity];
        CircularBS[startIndex % capacity] = null;
        entries -= 1;
        startIndex += 1;

        return output;
    }
    
    /**
     * no parameters, no return, Archives all entries in the array. Essentially dumps the contents. 
     */
    public void archiveAll(){
        int totalSize = size();
        if(isEmpty() == true){
            throw new NoBlockException("No Block to process");
        }
        else{
            for(int i = 0; i < totalSize; i++){
                archive();
            }
        }
        startIndex = 0;
        endIndex = capacity-1;
    }
    
    /**
     * no parameters, used to get the oldest entry to the array.
     * @return Most oldest entry of the array. 
     */
    public T getFront(){
        if(isEmpty() == true){
            throw new NoBlockException("No Block to process");
        }
        else{
            T output = CircularBS[startIndex % capacity];
            return output;
        }
    }
    
    /**
     * no parameters, the inverse of getFront.
     * @return Oldest entry of the array. 
     */
    public T getBack(){
        if(isEmpty() == true){
            throw new NoBlockException("No Block to process");
        }
        else{
            T output = CircularBS[endIndex % capacity];
            return output;
        }
    }

    /**
     * no parameters, returns the number of available "slots" in the array.
     * @return capacity of the array.
     */
    public int getStorageCapacity(){
        return capacity -1;
    }
    
    /**
     * no parameters, returns the number of available entries in the array.
     * @return entries in the array.
     */
    public int size(){
        return entries;
    }
    
    /**
     * No parameters, a method to check if the array is devoid of entries.
     * @return T/F depending on if there are entries. 
     */
    public boolean isEmpty(){
        if( size() == 0){
            return true;
        }
        else{
            return false;
        }
    }
    
    /**
     * No parameters, a method to check if the array has any available slots for entries. 
     * @return T/F depending on the number of entries. 
     */
    public boolean isFull(){
        if( entries == (capacity -1)){
            return true;
        }
        else{
            return false;
        }
    }
    
    /**
     * A void method with no return or parameters that doubles the capacity of the array while preserving order. 
     * Resets startIndex to 0, and endIndex to the last (most recent) entry. 
     */
    @SuppressWarnings("unchecked")
    void doubleCapacity(){
        T[] resized = (T[])new Object[capacity*2];
        for(int i = 0; i < capacity; i++){
            resized[i] = CircularBS[(startIndex + i) % capacity];
        }
        CircularBS = resized;
        startIndex = 0;
        endIndex = size() -1;
        capacity *= 2;
        //System.out.printf("| %d |\n", size());
    }
    
    /**
     * No parameters, returns the index of the 1st entry. 
     * @return startIndex of the array.
     */
    int getStart(){
        //System.out.print(startIndex);
        return startIndex % capacity;
    }
    
    /**
     * no parameters, returns the index of the last entry of the array.
     * @return endIndex of the array.
     */
    int getEnd(){
        //System.out.print(endIndex);
        return endIndex % capacity;
    }
    
    /**
     * no parameters, Overwrites the base toString method to allow for generics and more useful implementation. 
     * @return the string form of the generic items in the array.
     */
    public String toString(){
        String output = "[";
        if(isEmpty() == true){
            output += "]";
        }
        else{
            for(int i = 0; i < size() -1; i++){
                output += CircularBS[(startIndex + i) % capacity] + ",";
            }
            output += CircularBS[endIndex % capacity] + "]";
        }
        return output;
    }
    
    /**
     * The standard Main method. Used for testing of the class.
     * @param args the string arguments input via console. 
     */
    public static void main(String[] args) {

        CircularBS<String> ins= new CircularBS<>(5);
		
		try {
			System.out.println(ins.isEmpty());          // true
			System.out.println(ins.isFull());           //false
			System.out.println(ins);                     //[]
			System.out.println(ins.getStorageCapacity());     //4
			System.out.println(ins.size());            //0
			System.out.println(ins.getEnd());               //4
			System.out.println(ins.getStart());             //0
			ins.archive();                       // throws No Block to process
		}
        catch(Exception e) {
		    System.out.println(e.toString());
		}
		ins.insert("Adams");	
		ins.insert("Quency");
		ins.insert("Lincoln");	
		ins.insert("Malcom");
        ins.archive();
        ins.archive();
        ins.insert("Brown");
        ins.insert("King");
        System.out.println(ins.isFull());          //true
		System.out.println(ins);             //[Lincoln,Malcom,Brown,King]
		System.out.println(ins.getStorageCapacity());     //4
		System.out.println(ins.size());            //4
		System.out.println(ins.getEnd());               //0
		System.out.println(ins.getStart());            //2
		
		ins.insert("Lewis");
		System.out.println(ins.isFull());          //false
		System.out.println(ins);                   //[Lincoln,Malcom,Brown,King,Lewis]
		System.out.println(ins.getStorageCapacity());     //9
		System.out.println(ins.size());            //5
		System.out.println(ins.getEnd());               //4
		System.out.println(ins.getStart());             //0
		System.out.println(ins.getFront());       //Lincoln
		System.out.println(ins.getBack());        //Lewis
		
	    ins.insert("Liuzzo");
	    System.out.println(ins.getStorageCapacity());          //9
		System.out.println(ins);                      //[Lincoln,Malcom,Brown,King,Lewis,Liuzzo]
		ins.archiveAll();
		System.out.println(ins);                      //[]
		System.out.println(ins.getStorageCapacity());        //9
		System.out.println(ins.size());              //0
		System.out.println(ins.getEnd());                //9
		System.out.println(ins.getStart());              //0
		
		
		CircularBS<Double> ins2= new CircularBS<>();
		System.out.println(ins2.getStorageCapacity());      //49
		System.out.println(ins2.size());             //0
		System.out.println(ins2 instanceof CircularBSInterface);      //true;
		
	
	}
}
