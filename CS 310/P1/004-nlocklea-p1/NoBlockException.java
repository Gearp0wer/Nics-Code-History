/*
 * Author: Nicholas Locklear
 * G01090642
 * CS 310-004
 */

/**
 * NoBlockExeption is a custom (unchecked) exception used when operations are performed on an empty array. 
 */
public class NoBlockException extends RuntimeException{
    /**
     * Constructor of the exeption.
     * @param message is the message passed into the exception that is output when the exception is called.  
     */
    public NoBlockException(String message){
        super("No Block to process.");
    }
    
}
