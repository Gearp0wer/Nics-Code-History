
import java.util.*;
/*
 * todo:
 * card class
 * array of cards
 * blackjack rules
 */
public class initStartup {
    private int deckState;
    private int startingBet;
    private int total;
    private int bettingPool;
    private String[] playerHand;
    private String[] dealerHand;
    private String[] deckArray;

    public initStartup(){
        this.deckState = 0;
        this.startingBet = 10;
        this.bettingPool = 0;
        this.total = 0;
        this.playerHand = null;
        this.dealerHand = null;
        this.deckArray = null;
    }

    public static void main(String[] args){
        Scanner myObj = new Scanner(System.in);  
        System.out.println("Enter username");
    
        String userName = myObj.nextLine(); 
        System.out.println("Username is: " + userName); 
        
        String option = "";
        while(option != "4"){
            System.out.println("Please slect an option from the following");
            System.out.println("\n1): Start\n2)Options\n3)back4)Quit Program");
            switch (option) {
                case "1":
                    //launches blackjack
                    break;
                case "2":
                    // pulls up an options menu
                    break; 
                case "3":   
                    //goes back 1, to main menu (to select a different game)
                    break; 
                case "4":
                    System.out.println("Thanks for playing!\n");
                    myObj.close();
                    break;          
                default:
                    System.out.println("Error: [ " + option + " ] is invalid as an entry. Please try again.");
                    break;
            }
       } 
    }
}
