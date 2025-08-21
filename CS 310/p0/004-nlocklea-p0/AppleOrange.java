/*
 * Author: Nicholas Locklear
 * G01090642
 * CS 310-004
 */

/**
 * AppleOrange is a class that prints "apple" instead of x where x%3 = 0, and "orange" where x%7 = 0.
 */

public class AppleOrange{
    /**
     * Sets the upper ceiling to count to.
     * @param value for counting to.
     * @return none. 
     */
    private String input;

    /**
     *  Takes the user input, sets the class value to that input.
     * @param input the user input from main
     */
    public AppleOrange(String input){
        this.input = input;
    }
    /**
     * Input check if integer.
     * @param s the input string
     * @return a bool determining if the input was a valid integer
     */
    public boolean inputCheck(String s){
        try{
            Integer.parseInt(s);
            return true;
        }
        catch (NumberFormatException ex){
            return false;
        }
    }
    //these were probably unneeded
    /**
     * A statement to output "apple".
     */
    private void printApple(){
        System.out.print("apple");
    }
    /** 
     *A statement to output "orange".
     */
    private void printOrange(){
        System.out.print("orange");
    }
    
    /**
     * A method to give the output.
     * @param input the input from main, after verification.
     */
    private void systemOutput(int input){ 
        //I'm sure I could write this with ternary operators, but I can't be bothered right now
        for(int i = 1; i <= input; i ++){
            if(i % 3 == 0 || i% 7 == 0){
                if( i % 21 == 0){
                    printApple();
                    printOrange();
                    continue;
                }
                else{
                    if(i % 3 == 0){
                        printApple();
                        continue;
                    }
                    if(i % 7 == 0){
                        printOrange();
                        continue;
                    }
                }
            }
            else{
                System.out.print(i);
            }
        } 
    }
    //the try/catch for the input check to catch other possible errors. 
    /**
     * Reads the input given to the class, then does the grunt work of validating the input. 
     */
    private void inputMiddleman(){
        boolean check = inputCheck(this.input);
        int ceiling = 0;
        if(check != true || Integer.parseInt(this.input) < 1) {
            System.err.print("One positive number required as a command line argument.\nExample Usage: java AppleOrange [number]\n");
        }
        else{
            ceiling = Integer.parseInt(this.input);
            systemOutput(ceiling);
        }
    }
    /**
     * Its the main statement. 
     * @param args user input.
     */
    public static void main (String[] args) {
        if (args.length == 0 || args.length >1){
            System.err.print("One positive number required as a command line argument.\nExample Usage: java AppleOrange [number]\n");
        }
        else{
            AppleOrange object = new AppleOrange(args[0]);
            object.inputMiddleman();
        }

    }
}