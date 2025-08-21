/*
 * Author: Nicholas Locklear
 * G01090642
 * CS 310-004
 */
 
/**
 * The interface class for the project, defines the methods and return types for the other classes that use this. 
 * @param <T> is the variable denoting this as a generic interface. 
 */
interface CircularBSInterface<T> {

    /**
     * The insertion method, for putting new items in the array. 
     * @param inputblock is the generic item being inserted into the array. 
     */
    void insert(T inputblock);
    
    /**
     * No parameters, the method used to "archive" (remove) the oldest entry from the array.
     * @return Oldest entry in the array. 
     */
    T archive();

    /**
     * no parameters, no return, Archives all entries in the array. Essentially dumps the contents. 
     */    
    void archiveAll();

    /**
     * no parameters, used to get the oldest entry to the array.
     * @return Most oldest entry of the array. 
     */
    T getFront();

    /**
     * no parameters, the inverse of getFront.
     * @return Oldest entry of the array. 
     */
    T getBack();
    
    /**
     * no parameters, returns the number of available "slots" in the array.
     * @return capacity of the array.
     */
    int getStorageCapacity();

    /**
     * no parameters, returns the number of available entries in the array.
     * @return entries in the array.
     */
    int size();

    /**
     * No parameters, a method to check if the array is devoid of entries.
     * @return T/F depending on if there are entries. 
     */
    boolean isEmpty();

    /**
     * No parameters, a method to check if the array has any available slots for entries. 
     * @return T/F depending on the number of entries. 
     */
    boolean isFull();
}